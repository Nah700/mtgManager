/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** Core
*/

#include "Core.hpp"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp)
{
    userp->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string makeRequest(const std::string &url)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    return readBuffer;
}

Core::Core()
{
    this->_graphicPart = std::make_unique<Graphical>();
    this->_deckPath = "";
    this->_scene = 0;
}

bool findImageUrl(const Json::Value &json, std::string &imageUrl) {
    if (json.isObject()) {
        if (json.isMember("imageUrl")) {
            imageUrl = json["imageUrl"].asString();
            return true;
        }
        for (const auto &key : json.getMemberNames()) {
            if (findImageUrl(json[key], imageUrl)) {
                return true;
            }
        }
    } else if (json.isArray()) {
        for (const auto &element : json) {
            if (findImageUrl(element, imageUrl)) {
                return true;
            }
        }
    }
    return false;
}

void Core::initDeck()
{
    bool finished = false;
    std::thread deckLoadingThread([&finished, this]() {
        std::ifstream file(this->_deckPath);
        if (file.is_open()) {
            std::string line;
            std::vector<std::string> lines;
            while (std::getline(file, line)) {
                lines.push_back(line);
            }
            file.close();

            for (size_t i = 0; i < lines.size(); ++i) {
                line = lines[i];
                std::stringstream urlStream;
                urlStream << "https://api.magicthegathering.io/v1/cards?name=" << curl_easy_escape(curl_easy_init(), line.c_str(), line.size());

                std::string response = makeRequest(urlStream.str());

                Json::CharReaderBuilder reader;
                Json::Value jsonResponse;
                std::string errs;

                std::istringstream s(response);
                bool parsingSuccessful = Json::parseFromStream(reader, s, &jsonResponse, &errs);
                if (!parsingSuccessful) {
                    std::cerr << "Failed to parse JSON: " << errs << std::endl;
                    continue;
                }

                bool cardFound = false;
                if (!jsonResponse["cards"].isNull()) {
                    for (const auto &card : jsonResponse["cards"]) {
                        if (card["name"].asString() == line) {
                            cardFound = true;
                            std::string cardName = card["name"].asString();
                            std::string cardType = card["type"].asString();
                            std::string cardCost = card["manaCost"].asString();
                            std::string cardText = card["text"].asString();
                            std::string cardPower = "0";
                            std::string cardThougness = "0";
                            if (cardType.find("Creature") != std::string::npos) {
                                cardPower = card["power"].asString();
                                cardThougness = card["toughness"].asString();
                            }
                            std::string cardUrlImage;

                            if (!findImageUrl(card, cardUrlImage)) {
                                std::cerr << "imageUrl not found for card: " << cardName << std::endl;
                                continue;
                            }

                            checkUrl(cardUrlImage);
                            this->_cards.push_back(std::make_unique<ACard>(cardName, cardCost, cardType, cardText, cardUrlImage, std::make_pair(std::stoi(cardPower), std::stoi(cardThougness))));
                            break;
                        }
                    }
                }
                if (!cardFound) {
                    std::cerr << "Card not found: " << line << std::endl;
                }
                this->_graphicPart->displayLoadingBar((float)i / lines.size());
            }
        } else {
            std::cout << "Unable to open file: " << this->_deckPath << '\n';
        }
        finished = true;
    });
    while (deckLoadingThread.joinable()) {
        this->_graphicPart->displayWindowContent(this->_scene, this->_deckPath, *this->getCardByName(this->_graphicPart->getActiveCard()));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (finished) {
            break;
        }
    }

    deckLoadingThread.join();
}

void Core::updateSearchSuggestions() {
    std::string searchText = this->_graphicPart->getSearchBarText().getString().toAnsiString();
    std::vector<std::string> suggestions;

    for (const auto& card : this->_cards) {
        if (card->getName().substr(0, searchText.size()) == searchText) {
            suggestions.push_back(card->getName());
        }
    }

    this->_graphicPart->updateDropdownMenu(suggestions);
}

ACard *Core::getCardByName(std::string name)
{
    for (long unsigned int i = 0; i < this->_cards.size(); i++) {
        if (this->_cards[i]->getName() == name) {
            return this->_cards[i].get();
        }
    }
    return nullptr;
}

void Core::manageSearchBar(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        std::string clickedItem = this->_graphicPart->suggestClicked(event.mouseButton.x, event.mouseButton.y);
        if (this->_graphicPart->getSearchBar().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            this->isFocused = true;
            if (!isWriting) {
                this->_graphicPart->getSearchBarText().setString("");
                isWriting = true;
            }
        } else if (!clickedItem.empty()) {
                this->_graphicPart->getSearchBarText().setString(clickedItem);
                this->_graphicPart->updateDropdownMenu({});
        } else {
            this->isFocused = false;
            if (isWriting) {
                this->_graphicPart->getSearchBarText().setString("Search");
                this->_graphicPart->updateDropdownMenu({});
                isWriting = false;
            }
        }
    }
    if (this->isFocused && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\r') {
            std::cout << this->_graphicPart->getSearchBarText().getString().toAnsiString() << std::endl;
            this->_graphicPart->infoCardTexture(this->getCardByName(this->_graphicPart->getSearchBarText().getString().toAnsiString()));
            this->_graphicPart->addCardToBoard(this->_graphicPart->getSearchBarText().getString().toAnsiString());
            this->_graphicPart->getSearchBarText().setString("Search");
            this->_graphicPart->updateDropdownMenu({});
            isWriting = false;
        }
        else if (event.text.unicode == '\b') {
            std::string currentText = this->_graphicPart->getSearchBarText().getString().toAnsiString();
            if (!currentText.empty()) {
                currentText.pop_back();
                this->_graphicPart->getSearchBarText().setString(currentText);
            }
        }
        else {
            if (static_cast<char>(event.text.unicode) >= 32 && static_cast<char>(event.text.unicode) <= 126) {
                this->_graphicPart->getSearchBarText().setString(this->_graphicPart->getSearchBarText().getString() + static_cast<char>(event.text.unicode));
                this->updateSearchSuggestions();
            }
        }
    }
}

void Core::run()
{
    sf::Event event;

    while (this->_graphicPart->getWindow()->isOpen()) {
        while (this->_graphicPart->getWindow()->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->_graphicPart->getWindow()->close();
            this->manageSearchBar(event);
            this->_graphicPart->dragDropCard(event);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->_graphicPart->getEnlarged()) {
                this->_graphicPart->duplicateCard(this->_cards, this->getCardByName(this->_graphicPart->getActiveCard()));
            }
            this->_graphicPart->clickCardOnBoard(event);
            if (this->_graphicPart->getActiveCard() != "")
                this->_graphicPart->changeStats(event, this->getCardByName(this->_graphicPart->getActiveCard()));
        }
        this->_sceneFunctions[this->_scene]();
        this->_graphicPart->manageButtonCallback(this->_scene, this->_deckPath);
        this->_graphicPart->handleScrollEvent(event);
        this->_graphicPart->handleMouseClickEvent(event);
        this->_graphicPart->displayWindowContent(this->_scene, this->_deckPath, *this->getCardByName(this->_graphicPart->getActiveCard()));
    }
}

void Core::initCards()
{
    bool finished = false;
    std::thread cardsLoadingThread([&finished, this]() {
        for (long unsigned int i = 0; i < this->_cards.size(); i++) {
            this->_graphicPart->addCard(this->_cards[i]->getName(), this->_cards[i]->getTexturePath());
            this->_graphicPart->displayLoadingBar((float)i / this->_cards.size());
        }
        this->_deckPath = "";
        finished = true;
    });
    while (cardsLoadingThread.joinable()) {
        this->_graphicPart->displayWindowContent(this->_scene, this->_deckPath, *this->getCardByName(this->_graphicPart->getActiveCard()));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (finished) {
            break;
        }
    }
    cardsLoadingThread.join();
}

void Core::scene0()
{
    if (this->_deckPath != "") {
        this->initDeck();
        this->initCards();
        this->_scene++;
        this->_graphicPart->addButton(1800.0f, 10.0f, 100.0f, 100.0f, 1, "None", [this]() { return parameter(); }, "Parameter", sf::Color(255, 255, 255));
        this->_graphicPart->addButton(1500.0f, 10.0f, 100.0f, 100.0f, 1, "None", [this]() { return help_menu(); }, "Help", sf::Color(255, 255, 255));
    }
}

void Core::scene1()
{
    return;
}

void Core::scene2()
{
    return;
}

void Core::scene3()
{
    return;
}

std::string Core::parameter()
{
    this->_graphicPart->changeBackgroundTexture("GraphicUtils/Assets/Textures/parameter_background.png");
    this->_scene = 2;
    this->_graphicPart->addButton(10.0f, 10.0f, 100.0f, 100.0f, 2, "None", [this]() { return quitParam(); }, "return", sf::Color(255, 255, 255));
    return "";
}

std::string Core::quitParam()
{
    this->_graphicPart->changeBackgroundTexture("GraphicUtils/Assets/Textures/background.png");
    this->_scene = 1;
    return "";
}

std::string Core::help_menu()
{
    this->_graphicPart->changeBackgroundTexture("GraphicUtils/Assets/Textures/parameter_background.png");
    this->_scene = 3;
    this->_graphicPart->addButton(10.0f, 10.0f, 100.0f, 100.0f, 3, "None", [this]() { return quitHelp(); }, "return", sf::Color(255, 255, 255));
    return "";
}

std::string Core::quitHelp()
{
    this->_graphicPart->changeBackgroundTexture("GraphicUtils/Assets/Textures/background.png");
    this->_scene = 1;
    return "";
}

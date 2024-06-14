/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** Core
*/

#include "Core.hpp"

// Stocker la réponse
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp)
{
    userp->append((char *)contents, size * nmemb);
    return size * nmemb;
}

// Faire la requête GET à l'API
std::string makeRequest(const std::string &url) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
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

void Core::initDeck()
{
    std::ifstream file(this->_deckPath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            this->_cards.push_back(std::make_unique<ACard>(line));
            
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
                        std::cout << "Card name: " << cardName << std::endl;

                        std::string cardType = card["type"].asString();
                        std::cout << "Card type: " << cardType << std::endl;

                        std::string cardCost = card["manaCost"].asString();
                        std::cout << "Card Cost: " << cardCost << std::endl;

                        std::string cardText = card["text"].asString();
                        std::cout << "Card text: " << cardText << std::endl;

                        std::string cardUrlImage = card["imageUrl"].asString();
                        std::cout << "Card Image: " << cardUrlImage << std::endl;

                        // Uncomment these if needed
                        // this->_cards.back()->setName(cardName);
                        // this->_cards.back()->setCardType(cardType);
                        break;
                    }
                }
            }

            if (!cardFound) {
                std::cerr << "Card not found: " << line << std::endl;
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open file: " << this->_deckPath << '\n';
    }
    this->_deckPath = "";
    for (long unsigned int i = 0; i < this->_cards.size(); i++) {
        std::cout << this->_cards[i]->getName() << std::endl;
    }
    return;
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
        }
        this->_sceneFunctions[this->_scene]();
        this->_graphicPart->manageButtonCallback(this->_scene, this->_deckPath);
        this->_graphicPart->displayWindowContent(this->_scene);
    }
}

void Core::scene0()
{
    if (this->_deckPath != "") {
        this->initDeck();
        this->_scene++;
        this->_graphicPart->addButton(1800.0f, 10.0f, 100.0f, 100.0f, 1, "None", [this]() { return parameter(); }, "Parameter", sf::Color(255, 255, 255));
        this->_graphicPart->addButton(1280.0f, 100.0f, 20.0f, 100.0f, 1, "None", [this]() { return this->_graphicPart->toggleInfo(); }, ">", sf::Color(255, 255, 255));
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

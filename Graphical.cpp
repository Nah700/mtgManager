/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** Graphical
*/

#include "Graphical.hpp"

void Graphical::initInfoItems()
{
    this->_searchBar.setFillColor(sf::Color(70, 70, 70));
    this->_searchBar.setPosition(1350, 20);
    this->_searchBar.setSize(sf::Vector2f(200, 40));
    this->_searchBar.setOutlineColor(sf::Color(255, 255, 255));
    this->_searchBar.setOutlineThickness(1.0f);
    this->_font.loadFromFile("GraphicUtils/Assets/Fonts/arial.ttf");
    this->_searchBarText.setFont(this->_font);
    this->_searchBarText.setString("Search");
    this->_searchBarText.setCharacterSize(18);
    this->_searchBarText.setFillColor(sf::Color(255, 255, 255));
    this->_searchBarText.setPosition(1360, 20);
    this->_infoView.setFillColor(sf::Color(70, 70, 70));
    this->_infoView.setPosition(1300, 0);
    this->_infoView.setSize(sf::Vector2f(620, 1080));
    this->_cardInfoView.setPosition(1478, 300);
    this->_cardInfoView.setSize(sf::Vector2f(265, 370));

    this->_checkbox1.setSize(sf::Vector2f(20, 20));
    this->_checkbox1.setFillColor(sf::Color::White);
    this->_checkbox1.setPosition(900, 850);
    this->_checkbox1.setOutlineColor(sf::Color::Red);
    this->_checkbox1.setOutlineThickness(2);
    this->_checkbox2.setSize(sf::Vector2f(20, 20));
    this->_checkbox2.setFillColor(sf::Color::White);
    this->_checkbox2.setPosition(900, 880);
    this->_checkbox2.setOutlineColor(sf::Color::Green);
    this->_checkbox2.setOutlineThickness(2);
}

void Graphical::initLoading()
{
    this->_loadingBar.setSize(sf::Vector2f(500, 30));
    this->_loadingBar.setPosition(710, 525);
    this->_loadingBar.setFillColor(sf::Color(70, 70, 70));
    this->_loadingBar.setOutlineColor(sf::Color(255, 255, 255));
    this->_loadingBar.setOutlineThickness(1.0f);

    this->_loadingBarProgress.setSize(sf::Vector2f(0, 30));
    this->_loadingBarProgress.setPosition(710, 525);
    this->_loadingBarProgress.setFillColor(sf::Color(255, 255, 255));

    this->_loadingBarText.setFont(this->_font);
    this->_loadingBarText.setString("Loading...");
    this->_loadingBarText.setCharacterSize(18);
    this->_loadingBarText.setFillColor(sf::Color(255, 255, 255));
    this->_loadingBarText.setPosition(810, 425);
}

void Graphical::initRules() {
    this->_helpMenu.setSize(sf::Vector2f(500, 1080));
    this->_helpMenu.setPosition(sf::Vector2f((1920 / 2), 0));
    this->_helpMenu.setFillColor(sf::Color(220, 220, 220, 255));

    this->_helpMenuText.setFont(this->_font);
    this->_helpMenuText.setCharacterSize(20);
    this->_helpMenuText.setFillColor(sf::Color::Black);
    this->_helpMenuText.setPosition(sf::Vector2f((1920 / 2) + 10, 10));

    std::ifstream rulesFile("keyWord.txt");
    if (rulesFile.is_open()) {
        std::string line;
        std::string ruleNumber;
        std::string ruleName;
        std::stringstream ruleContent;

        while (std::getline(rulesFile, line)) {
            if (line.find(".") != std::string::npos) {
                if (!ruleNumber.empty() && !ruleName.empty()) {
                    _rules.push_back(std::make_pair(ruleNumber + " " + ruleName, ruleContent.str()));
                    _ruleTitles.push_back(ruleNumber + " " + ruleName);
                    ruleContent.str(std::string());
                    ruleContent.clear();
                }

                size_t dotPos = line.find(".");
                ruleNumber = line.substr(0, dotPos);
                ruleName = line.substr(dotPos + 1);
            } else {
                ruleContent << line << "\n";
            }
        }

        if (!ruleNumber.empty() && !ruleName.empty()) {
            _rules.push_back(std::make_pair(ruleNumber + " " + ruleName, ruleContent.str()));
            _ruleTitles.push_back(ruleNumber + " " + ruleName);
        }

        rulesFile.close();
    } else {
        std::cerr << "Unable to open rules file!" << std::endl;
    }

    _selectedRuleIndex = -1;

    _ruleDefinitionText.setFont(_font);
    _ruleDefinitionText.setCharacterSize(20);
    _ruleDefinitionText.setFillColor(sf::Color::Black);
    _ruleDefinitionText.setPosition(sf::Vector2f((1920 / 2) + 10, 500));
}

void Graphical::handleRuleSelection(int selectedIndex) {
    if (selectedIndex >= 0 && selectedIndex < _rules.size()) {
        _selectedRuleIndex = selectedIndex;
        _ruleDefinitionText.setString(_rules[_selectedRuleIndex].second);
    }
}

Graphical::Graphical()
{
    this->_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "MTGMANAGER");
    this->addButton(850.0f, 450.0f, 200.0f, 100.0f, 0, "None", openFileExplorer, "Select deck", sf::Color(255, 255, 255));
    this->addButton(1280.0f, 100.0f, 20.0f, 100.0f, 1, "None", [this]() { return this->toggleInfo(); }, ">", sf::Color(255, 255, 255));
    this->addButton(1478.0f, 700.0f, 265.0f, 50.0f, 1, "None", [this]() { return this->addCardToBoard(std::string("None")); }, "Add to battlefield", sf::Color(255, 255, 255));
    this->_backgroundTexture = std::make_unique<sf::Texture>();
    if (!this->_backgroundTexture->loadFromFile("GraphicUtils/Assets/Textures/background.png"))
        std::cerr << "Failed to load background texture" << std::endl;
    this->_background.setTexture(this->_backgroundTexture.get());
    this->_background.setPosition(0, 0);
    this->_background.setSize(sf::Vector2f(1920, 1080));
    this->initInfoItems();
    this->initLoading();

    //new
    this->_selectedRuleIndex = -1;
    this->initRules();
}

Graphical::~Graphical()
{
    delete this->_window;
}

void Graphical::addButton(float x, float y, float width, float height, int scene, std::string text, std::function<std::string()> callback, std::string buttonText, sf::Color color)
{
    this->_buttons.push_back(std::make_unique<Button>(x, y, width, height, scene, text, callback, buttonText, color));
}

sf::RenderWindow *Graphical::getWindow()
{
    return this->_window;
}

std::vector<std::unique_ptr<Button>> &Graphical::getButtons()
{
    return this->_buttons;
}

void Graphical::infoCardTexture(ACard *card)
{
    if (card == nullptr)
        this->_cardInfoView.setTexture(nullptr);
    else
        this->_cardInfoView.setTexture(loadTextureFromUrl(card->getTexturePath(), card->getName() + ".png"));
}

void Graphical::addCard(std::string name, std::string texturePath)
{
    std::unique_ptr<sf::RectangleShape> rectangle = std::make_unique<sf::RectangleShape>();
    rectangle->setTexture(loadTextureFromUrl(texturePath, name + ".png"));
    rectangle->setSize(sf::Vector2f(200, 300));
    rectangle->setPosition(100, 100);
    this->_rectangles.push_back(std::make_tuple(std::move(rectangle), false, name));
}

void Graphical::createDeck(std::vector<std::unique_ptr<ACard>> cartes)
{
    for (auto &card : cartes) {
        this->addCard(card->getName(), card->getTexturePath());
    }
}

std::string Graphical::toggleInfo()
{
    if (this->_infoViewIsOpen) {
        this->_infoView.setPosition(1920.0f, 100.0f);
        this->_searchBar.setPosition(1970.0f, 20.0f);
        this->_searchBarText.setPosition(1980.0f, 20.0f);
        this->getButtonByText(">")->getButton().setPosition(1900.0f, 100.0f);
        this->getButtonByText(">")->getButtonText().setPosition(
            this->getButtonByText(">")->getButton().getPosition().x + (this->getButtonByText(">")->getButton().getSize().x - this->getButtonByText(">")->getButtonText().getGlobalBounds().width) / 2,
            this->getButtonByText(">")->getButton().getPosition().y + (this->getButtonByText(">")->getButton().getSize().y - this->getButtonByText(">")->getButtonText().getGlobalBounds().height) / 2 - 5
        );
        this->_cardInfoView.setPosition(1950, 300);
        this->getButtonByText(">")->changeButtonText("<");
        this->_infoViewIsOpen = false;
    } else {
        this->_infoView.setPosition(1300.0f, 0.0f);
        this->_searchBar.setPosition(1350.0f, 20.0f);
        this->_searchBarText.setPosition(1360.0f, 20.0f);
        this->getButtonByText("<")->getButton().setPosition(1280.0f, 100.0f);
        this->getButtonByText("<")->getButtonText().setPosition(
            this->getButtonByText("<")->getButton().getPosition().x + (this->getButtonByText("<")->getButton().getSize().x - this->getButtonByText("<")->getButtonText().getGlobalBounds().width) / 2,
            this->getButtonByText("<")->getButton().getPosition().y + (this->getButtonByText("<")->getButton().getSize().y - this->getButtonByText("<")->getButtonText().getGlobalBounds().height) / 2 - 5
        );
        this->_cardInfoView.setPosition(1478, 300);
        this->getButtonByText("<")->changeButtonText(">");
        this->_infoViewIsOpen = true;
    }
    return "";
}

void Graphical::displayWindowContent(int scene, std::string &deckPath)
{
    this->_window->clear();
    this->_window->draw(this->_background);

    if (scene == 0 && deckPath != "") {
        this->_window->draw(this->_loadingBar);
        this->_window->draw(this->_loadingBarProgress);
        this->_window->draw(this->_loadingBarText);
    }

    if (scene == 1) {
        this->_window->draw(this->_infoView);
        this->_window->draw(this->_searchBar);
        this->_window->draw(this->_searchBarText);
        this->_window->draw(this->_cardInfoView);

        for (const auto &menuText : this->_dropdownMenu) {
            this->_window->draw(*menuText);
        }

        for (const auto &card : this->_rectangles) {
            if (std::get<1>(card)) {
                this->_window->draw(*std::get<0>(card));
            }
        }

        if (this->_cardEnlarged) {
            this->_window->draw(this->_checkbox1);
            this->_window->draw(this->_checkbox2);
        }
    }

    for (const auto &button : this->_buttons) {
        if (scene == button->getScene()) {
            if (button->getButtonText().getString() == "Parameter" && this->_infoViewIsOpen) {
                continue;
            }
            if (button->getButtonText().getString() == "Add to battlefield" && !this->_infoViewIsOpen) {
                continue;
            }
            this->_window->draw(button->getButton());
            this->_window->draw(button->getButtonText());
        }
    }

    if (scene == 3) {
        this->_window->draw(this->_helpMenu);
        float menuY = 10.0f;
        std::set<std::string> ruleNumbers;

        // Identifier les noms de règles et collecter les définitions
        std::vector<std::pair<std::string, std::vector<std::string>>> ruleDefinitions;

        for (size_t i = 0; i < _rules.size(); ++i) {
            std::string fullRule = _rules[i].first;
            size_t found = fullRule.find_first_of("0123456789");
            if (found != std::string::npos) {
                std::string ruleNumber = fullRule.substr(found);
                ruleNumbers.insert(ruleNumber);
            }
        }

        for (const auto& ruleNumber : ruleNumbers) {
            sf::Text ruleText;
            ruleText.setFont(this->_font);
            ruleText.setCharacterSize(20);
            ruleText.setFillColor(sf::Color::Black);
            ruleText.setString(ruleNumber);
            ruleText.setPosition(sf::Vector2f((1920 / 2) + 10, menuY));
            this->_window->draw(ruleText);
            menuY += 30.0f;
        }

        if (_selectedRuleIndex >= 0 && _selectedRuleIndex < _rules.size()) {
            this->_helpMenuText.setString(_rules[_selectedRuleIndex].first);
            this->_selectedRuleText.setString(_rules[_selectedRuleIndex].second);
            this->_selectedRuleText.setPosition(sf::Vector2f((1920 / 2) + 10, menuY));
            this->_window->draw(this->_helpMenuText);
            this->_window->draw(this->_selectedRuleText);
        }
    }

    this->_window->display();
}

void Graphical::setVisibleCard(std::string cardName, bool visible)
{
    for (auto &card : this->_rectangles) {
        if (visible && std::get<2>(card) == cardName) {
            std::get<1>(card) = true;
            break;
        }
        if (!visible && std::get<2>(card) == cardName) {
            std::get<1>(card) = false;
            break;
        }
    }
}

void Graphical::manageButtonCallback(int scene, std::string &deckPath)
{
    for (auto &button : this->_buttons) {
        if (button->getButton().getGlobalBounds().contains(sf::Mouse::getPosition(*this->_window).x, sf::Mouse::getPosition(*this->_window).y)) {
            if ((button->getButtonText().getString() == "Parameter" && this->_infoViewIsOpen) || (button->getButtonText().getString() == "Add to battlefield" && !this->_infoViewIsOpen))
                continue;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                button->setButtonColor(sf::Color(10, 255, 10));
                std::string callbackResult = button->executeCallback();
                if (scene == 0 && callbackResult[0] == '/') {
                    deckPath = callbackResult;
                    this->_buttons.erase(this->_buttons.begin());
                }
                return;
            } else
                button->setButtonColor(sf::Color(255, 0, 0));
        } else
            button->setButtonColor(sf::Color(10, 10, 255));
    }
    for (auto &text : this->_dropdownMenu) {
        if (text->getGlobalBounds().contains(sf::Mouse::getPosition(*this->_window).x, sf::Mouse::getPosition(*this->_window).y))
            text->setFillColor(sf::Color(255, 0, 0));
        else
            text->setFillColor(sf::Color(255, 255, 255));
    }

    if (scene == 3) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mouse = sf::Mouse::getPosition(*this->_window);
            if (mouse.x >= (1920 / 2) && mouse.x <= ((1920 / 2) + 500) && mouse.y >= 0 && mouse.y <= 1080) {
                int index = (mouse.y - 10) / 30;

                if (index >= 0 && index < _rules.size()) {
                    _selectedRuleIndex = index;
                } else {
                    _selectedRuleIndex = -1;
                }
            }
        }
    }
}

void Graphical::changeBackgroundTexture(std::string texturePath)
{
    if (!this->_backgroundTexture->loadFromFile(texturePath))
        std::cerr << "Failed to load background texture" << std::endl;
    this->_background.setTexture(this->_backgroundTexture.get());
}

std::unique_ptr<Button> &Graphical::getButtonByText(std::string text)
{
    for (auto &button : this->_buttons)
        if (button->getButtonText().getString() == text)
            return button;
    throw std::invalid_argument("Button not found");
}

void Graphical::updateDropdownMenu(const std::vector<std::string>& suggestions)
{
    this->_dropdownMenu.clear();

    for (int i = 0; i < std::min(5, (int)suggestions.size()); i++)
        this->_dropdownMenu.push_back(std::make_unique<sf::Text> (suggestions[i], this->_font, 18));
}

std::string Graphical::suggestClicked(int x, int y)
{
    for (long unsigned int i = 0; i < this->_dropdownMenu.size(); i++)
        if (this->_dropdownMenu[i]->getGlobalBounds().contains(x, y))
            return this->_dropdownMenu[i]->getString().toAnsiString();
    return "";
}

void Graphical::displayLoadingBar(float progress)
{
    progress = std::max(0.0f, std::min(1.0f, progress));

    sf::Vector2f size = this->_loadingBar.getSize();
    this->_loadingBarProgress.setSize(sf::Vector2f(size.x * progress, size.y));

    int percentage = static_cast<int>(progress * 100);
    this->_loadingBarText.setString("Loading... " + std::to_string(percentage) + "%");
}

std::string Graphical::addCardToBoard(std::string cardName)
{
    if (cardName != "None") {
        this->_activeCard = cardName;
        return "";
    }
    if (cardName == "None") {
        for (auto &card : this->_rectangles) {
            if (std::get<2>(card) == this->_activeCard) {
                this->setVisibleCard(this->_activeCard, true);
                break;
            }
        }
    }
    this->_dragDrop = true;
    return "";
}

void Graphical::dragDropCard(sf::Event event)
{
    if (this->_dragDrop) {
        if (event.type == sf::Event::MouseButtonPressed) {
            this->_dragDrop = false;
        } else if (event.type == sf::Event::MouseMoved) {
            for (auto &card : this->_rectangles) {
                if (std::get<1>(card) && std::get<2>(card) == this->_activeCard) {
                    std::get<0>(card)->setPosition(float(event.mouseMove.x), float(event.mouseMove.y));
                    break;
                }
            }
        }
    }
}

void Graphical::moveCardToBack(std::string cardName)
{
    for (auto card = this->_rectangles.begin(); card != this->_rectangles.end(); card++) {
        if (std::get<2>(*card) == cardName) {
            this->_rectangles.push_back(std::move(*card));
            this->_rectangles.erase(card);
            break;
        }
    }
}

void Graphical::clickCardOnBoard(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        bool clickedOnCard = false;
        for (auto &card : this->_rectangles) {
            auto &rectangle = std::get<0>(card);
            if (rectangle->getGlobalBounds().contains(float(event.mouseButton.x), float(event.mouseButton.y))) {
                clickedOnCard = true;
                if (_cardEnlarged && std::get<2>(card) != this->_activeCard) {
                    for (auto &prevCard : this->_rectangles) {
                        if (std::get<2>(prevCard) == this->_activeCard) {
                            if (this->_infoViewIsOpen) {
                                this->toggleInfo();
                            }
                            auto &prevRectangle = std::get<0>(prevCard);
                            prevRectangle->setSize(this->_originalCardSize);
                            prevRectangle->setPosition(this->_originalCardPosition);
                            break;
                        }
                    }
                }
                if (!_cardEnlarged || std::get<2>(card) != this->_activeCard) {
                    if (this->_infoViewIsOpen) {
                        this->toggleInfo();
                    }
                    this->_originalCardPosition = rectangle->getPosition();
                    this->_originalCardSize = rectangle->getSize();
                    rectangle->setSize(sf::Vector2f(400, 600));
                    rectangle->setPosition(960 - 200, 540 - 300);
                    this->_cardEnlarged = true;
                    this->_activeCard = std::get<2>(card);
                    this->moveCardToBack(this->_activeCard);
                }
                break;
            }
        }
        if (!clickedOnCard && _cardEnlarged) {
            bool updateOutline = false;
            if (_checkbox1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                _checkbox1Checked = !_checkbox1Checked;
                updateOutline = true;
            } else if (_checkbox2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                _checkbox2Checked = !_checkbox2Checked;
                updateOutline = true;
            }
            if (updateOutline) {
                sf::Color borderColor = sf::Color::Transparent;
                if (_checkbox1Checked) borderColor = sf::Color::Red;
                if (_checkbox2Checked) borderColor = sf::Color::Green;

                for (auto &card : _rectangles) {
                    if (std::get<2>(card) == _activeCard) {
                        auto &rectangle = std::get<0>(card);
                        rectangle->setOutlineColor(borderColor);
                        rectangle->setOutlineThickness(5);
                        return;
                    }
                }
            } else {
                for (auto &card : this->_rectangles) {
                    if (std::get<2>(card) == this->_activeCard) {
                        auto &rectangle = std::get<0>(card);
                        rectangle->setSize(this->_originalCardSize);
                        rectangle->setPosition(this->_originalCardPosition);
                        this->_cardEnlarged = false;
                        this->_activeCard = "";
                        break;
                    }
                }
            }
        }
    }
}


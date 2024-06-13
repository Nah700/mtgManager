/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** Graphical
*/

#include "Graphical.hpp"

Graphical::Graphical()
{
    this->_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "MTGMANAGER");
    this->addButton(850.0f, 450.0f, 200.0f, 100.0f, 0, "None", openFileExplorer, "Select deck", sf::Color(255, 255, 255));
    this->_backgroundTexture = std::make_unique<sf::Texture>();
    if (!this->_backgroundTexture->loadFromFile("GraphicUtils/Assets/Textures/background.png"))
        std::cerr << "Failed to load background texture" << std::endl;
    this->_background.setTexture(this->_backgroundTexture.get());
    this->_background.setPosition(0, 0);
    this->_background.setSize(sf::Vector2f(1920, 1080));
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
        this->getButtonByText("<")->changeButtonText(">");
        this->_infoViewIsOpen = true;
    }
    return "";
}

void Graphical::displayWindowContent(int scene)
{
    this->_window->clear();
    this->_window->draw(this->_background);
    for (auto &button : this->_buttons) {
        if (scene == button->getScene()) {
            this->_window->draw(button->getButton());
            this->_window->draw(button->getButtonText());
        }
    }
    if (scene == 1) {
        this->_window->draw(this->_infoView);
        this->_window->draw(this->_searchBar);
        this->_window->draw(this->_searchBarText);
        for (long unsigned int i = 0; i < this->_dropdownMenu.size(); i++) {
            this->_dropdownMenu[i]->setPosition(1360, 60 + i * 20);
            this->_window->draw(*this->_dropdownMenu[i]);
        }
    }
    this->_window->display();
}

void Graphical::manageButtonCallback(int scene, std::string &deckPath)
{
    for (auto &button : this->_buttons) {
        if (button->getButton().getGlobalBounds().contains(sf::Mouse::getPosition(*this->_window).x, sf::Mouse::getPosition(*this->_window).y)) {
            if (button->getButtonText().getString() == "Parameter" && this->_infoViewIsOpen)
                continue;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                button->setButtonColor(sf::Color(10, 255, 10));
                std::string callbackResult = button->executeCallback();
                if (scene == 0 && callbackResult[0] == '/') {
                    deckPath = callbackResult;
                    this->_buttons.erase(this->_buttons.begin());
                }
                return;
            } else {
                button->setButtonColor(sf::Color(255, 0, 0));
            }
        } else {
            button->setButtonColor(sf::Color(10, 10, 255));
        }
    }
    for (auto &text : this->_dropdownMenu) {
        if (text->getGlobalBounds().contains(sf::Mouse::getPosition(*this->_window).x, sf::Mouse::getPosition(*this->_window).y)) {
            text->setFillColor(sf::Color(255, 0, 0));
        } else {
            text->setFillColor(sf::Color(255, 255, 255));
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
    for (auto &button : this->_buttons) {
        if (button->getButtonText().getString() == text)
            return button;
    }
    throw std::invalid_argument("Button not found");
}

void Graphical::updateDropdownMenu(const std::vector<std::string>& suggestions)
{
    this->_dropdownMenu.clear();

    for (int i = 0; i < std::min(5, (int)suggestions.size()); i++) {
        this->_dropdownMenu.push_back(std::make_unique<sf::Text> (suggestions[i], this->_font, 18));
    }
}

std::string Graphical::suggestClicked(int x, int y)
{
    for (long unsigned int i = 0; i < this->_dropdownMenu.size(); i++) {
        if (this->_dropdownMenu[i]->getGlobalBounds().contains(x, y)) {
            return this->_dropdownMenu[i]->getString().toAnsiString();
        }
    }
    return "";
}

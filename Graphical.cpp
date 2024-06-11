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
    this->_isDeckSelected = false;
    this->_buttons.push_back(std::make_unique<Button>(850.0f, 450.0f, 200.0f, 100.0f, "None", openFileExplorer,"Deck", sf::Color(255, 255, 255)));
    this->_backgroundTexture = std::make_unique<sf::Texture>();
    if (!this->_backgroundTexture->loadFromFile("GraphicUtils/Assets/Textures/background.png"))
        std::cerr << "Failed to load background texture" << std::endl;
    this->_background.setTexture(this->_backgroundTexture.get());
    this->_background.setPosition(0, 0);
    this->_background.setSize(sf::Vector2f(1920, 1080));
}

Graphical::~Graphical()
{
    delete this->_window;
}

sf::RenderWindow *Graphical::getWindow()
{
    return this->_window;
}

std::vector<std::unique_ptr<Button>> &Graphical::getButtons()
{
    return this->_buttons;
}

void Graphical::displayWindowContent()
{
    this->_window->clear();
    this->_window->draw(this->_background);
    for (auto &button : this->_buttons) {
        this->_window->draw(button->getButton());
        this->_window->draw(button->getButtonText());
    }
    this->_window->display();
}

void Graphical::manageButtonCallback(std::string &deckPath)
{
    for (auto &button : this->_buttons) {
        if (button->getButton().getGlobalBounds().contains(sf::Mouse::getPosition(*this->_window).x, sf::Mouse::getPosition(*this->_window).y)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                button->setButtonColor(sf::Color(10, 255, 10));
                std::string callbackResult = button->executeCallback();
                if (callbackResult[0] == '/') {
                    deckPath = callbackResult;
                    this->_buttons.erase(this->_buttons.begin());
                }
            } else {
                button->setButtonColor(sf::Color(255, 0, 0));
            }
        } else {
            button->setButtonColor(sf::Color(10, 10, 255));
        }
    }
}


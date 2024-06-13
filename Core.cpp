/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** Core
*/

#include "Core.hpp"

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

void Core::manageSearchBar(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (this->_graphicPart->getSearchBar().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            this->isFocused = true;
            if (!isWriting) {
                this->_graphicPart->getSearchBarText().setString("");
                isWriting = true;
            }
        } else {
            this->isFocused = false;
            if (isWriting) {
                this->_graphicPart->getSearchBarText().setString("Search");
                isWriting = false;
            }
        }
    }
    if (this->isFocused && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\r') {
            std::cout << this->_graphicPart->getSearchBarText().getString().toAnsiString() << std::endl;
        }
        else if (event.text.unicode == '\b') {
            std::string currentText = this->_graphicPart->getSearchBarText().getString().toAnsiString();
            if (!currentText.empty()) {
                currentText.pop_back();
                this->_graphicPart->getSearchBarText().setString(currentText);
            }
        }
        else {
            if (static_cast<char>(event.text.unicode) >= 32 && static_cast<char>(event.text.unicode) <= 126)
                this->_graphicPart->getSearchBarText().setString(this->_graphicPart->getSearchBarText().getString() + static_cast<char>(event.text.unicode));
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

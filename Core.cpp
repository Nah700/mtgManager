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
    for (int i = 0; i < this->_cards.size(); i++) {
        std::cout << this->_cards[i]->getName() << std::endl;
    }
    return;
}

void Core::run()
{
    sf::Event event;

    while (this->_graphicPart->getWindow()->isOpen()) {
        while (this->_graphicPart->getWindow()->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->_graphicPart->getWindow()->close();
        }
        if (this->_deckPath != "")
            this->initDeck();
        this->_graphicPart->manageButtonCallback(this->_deckPath);
        this->_graphicPart->displayWindowContent();
    }
}


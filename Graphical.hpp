/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** Graphical
*/

#ifndef GRAPHICAL_HPP_
#define GRAPHICAL_HPP_

#include "GraphicUtils/Button.hpp"

class Graphical {
    public:
        Graphical();
        ~Graphical();

        sf::RenderWindow *getWindow();
        std::vector<std::unique_ptr<Button>> &getButtons();
        void displayWindowContent();
        void manageButtonCallback(std::string &deckPath);
    private:
        sf::RenderWindow *_window;
        bool _isDeckSelected;
        std::vector<std::unique_ptr<sf::RectangleShape>> _rectangles;
        std::vector<std::unique_ptr<Button>> _buttons;
        sf::RectangleShape _background;
        std::unique_ptr<sf::Texture> _backgroundTexture;

};

#endif /* !GRAPHICAL_HPP_ */

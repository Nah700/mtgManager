/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "../mtgManager.hpp"

class Button {
    public:
        template <typename Func>
        Button(float x, float y, float width, float height, std::string texturePath, Func &&func, std::string text = "None", sf::Color textColor = {255, 255, 255})
        {
            this->_button.setSize(sf::Vector2f(width, height));
            this->_button.setPosition(x, y);
            if (texturePath != "None") {
                this->_buttonTexture.loadFromFile(texturePath);
                this->_button.setTexture(&this->_buttonTexture);
            } else {
                this->_button.setFillColor(sf::Color(10, 10, 255));
            }
            if (text == "None")
                return;

            if (!this->_font.loadFromFile("GraphicUtils/Assets/Fonts/arial.ttf")) {
                std::cerr << "Error loading font\n";
                return;
            }
            this->_buttonText.setString(text);
            this->_buttonText.setFont(this->_font);
            this->_buttonText.setCharacterSize(20);
            this->_buttonText.setFillColor(textColor);
            this->_buttonText.setPosition(
                this->_button.getPosition().x + (this->_button.getSize().x - this->_buttonText.getGlobalBounds().width) / 2,
                this->_button.getPosition().y + (this->_button.getSize().y - this->_buttonText.getGlobalBounds().height) / 2 - 5
            );
            this->_buttonFunction = std::forward<Func>(func);
        }
        ~Button() = default;

        std::string executeCallback();
        sf::RectangleShape getButton();
        sf::Text getButtonText();
        void setButtonColor(sf::Color color);
    private:
        sf::RectangleShape _button;
        sf::Text _buttonText;
        sf::Font _font;
        sf::Texture _buttonTexture;
        std::function<std::string()> _buttonFunction;

};

#endif /* !BUTTON_HPP_ */

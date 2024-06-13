/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** Button
*/

#include "Button.hpp"

sf::RectangleShape &Button::getButton()
{
    return this->_button;
}

sf::Text &Button::getButtonText()
{
    return this->_buttonText;
}

void Button::setButtonColor(sf::Color color)
{
    this->_button.setFillColor(color);
}

std::string Button::executeCallback()
{
    return this->_buttonFunction();
}

void Button::changeButtonText(std::string text)
{
    this->_buttonText.setString(text);
}

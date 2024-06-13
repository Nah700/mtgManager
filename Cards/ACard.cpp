/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** ACard
*/

#include "ACard.hpp"

ACard::ACard(std::string name)
{
    this->_name = name;
}

std::string ACard::getName()
{
    return this->_name;
}

std::unordered_map<ManaType, int> ACard::getManaCost()
{
    return this->_manaCost;
}

CardType ACard::getCardType()
{
    return this->_cardType;
}

void ACard::setManaCost(const std::unordered_map<ManaType, int>& manaCost) {
    this->_manaCost = manaCost;
}

void ACard::setCardType(CardType cardType) {
    this->_cardType = cardType;
}
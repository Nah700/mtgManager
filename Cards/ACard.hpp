/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** ACard
*/

#ifndef ACARD_HPP_
#define ACARD_HPP_

#include "ICard.hpp"

class ACard : public ICard {
    public:
        ACard(std::string name, std::string manaCost, std::string cardtype, std::string text, std::string url);
        ~ACard() = default;

        std::string getName();
        std::unordered_map<ManaType, int> getManaCost();
        std::vector<CardType> getCardType();
        std::string getTexturePath();

        std::unordered_map<ManaType, int> setManaCost(std::string cost);
        std::vector<CardType> setCardType(std::string type);

    private:
        std::string _name;
        std::unordered_map<ManaType, int> _manaCost;
        std::vector<CardType> _cardType;
        std::string _text;
        std::string _texturePath;
};

#endif /* !ACARD_HPP_ */

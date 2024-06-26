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
        ACard(std::string name, std::string manaCost, std::string cardtype, std::string text, std::string url, std::pair<int, int> powerToughness);
        ~ACard() = default;

        std::string getName();
        std::unordered_map<ManaType, int> getManaCost();
        std::string getCardText();
        std::vector<CardType> getCardType();
        std::string getCardTypeStringed();
        std::string getTexturePath();
        int getPower();
        int getToughness();
        void setPower(int power);
        void setToughness(int toughness);
        std::string getOriginalManaCost();


        std::unordered_map<ManaType, int> setManaCost(std::string cost);
        std::vector<CardType> setCardType(std::string type);

    private:
        std::string _name;
        std::unordered_map<ManaType, int> _manaCost;
        std::string _manaCostString;
        std::vector<CardType> _cardType;
        std::string _cardTypeString;
        std::string _text;
        std::string _texturePath;
        std::pair<int, int> _powerToughness;
};

#endif /* !ACARD_HPP_ */

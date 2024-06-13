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
        ACard(std::string name);
        ~ACard() = default;

        std::string getName();
        std::unordered_map<ManaType, int> getManaCost();
        CardType getCardType();

        void setManaCost(const std::unordered_map<ManaType, int>& manaCost);
        void setCardType(CardType cardType);
        //void setCardText(std::string text);

    private:
        std::string _name;
        std::unordered_map<ManaType, int> _manaCost;
        CardType _cardType;
};

#endif /* !ACARD_HPP_ */

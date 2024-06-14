/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** ICard
*/

#ifndef ICARD_HPP_
#define ICARD_HPP_

#include "../mtgManager.hpp"

class ICard {
    public:
        virtual ~ICard() = default;
        virtual std::string getName() = 0;
        virtual std::unordered_map<ManaType, int> getManaCost() = 0;
        virtual std::vector<CardType> getCardType() = 0;
    private:
};

#endif /* !ICARD_HPP_ */

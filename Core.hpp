/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "mtgManager.hpp"
#include "Cards/ACard.hpp"
#include "Graphical.hpp"

class Core {
    public:
        Core();
        ~Core() = default;

        void initDeck();
        void run();

    protected:
    private:
        std::string _deckPath;
        std::vector<std::unique_ptr<ACard>> _cards;
        std::unique_ptr<Graphical> _graphicPart;
};

#endif /* !CORE_HPP_ */

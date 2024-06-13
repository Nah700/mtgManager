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
        void scene0();
        void scene1();
        void scene2();
        std::string parameter();
        std::string quitParam();

    protected:
    private:
        std::string _deckPath;
        std::vector<std::unique_ptr<ACard>> _cards;
        std::unique_ptr<Graphical> _graphicPart;
        int _scene;
        std::function<void()> _sceneFunctions[3] = {[this](){ scene0(); }, [this](){ scene1(); }, [this](){ scene2(); }};
};

#endif /* !CORE_HPP_ */

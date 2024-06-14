/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** Graphical
*/

#ifndef GRAPHICAL_HPP_
#define GRAPHICAL_HPP_

#include "GraphicUtils/Button.hpp"
#include "Cards/ACard.hpp"

class Graphical {
    public:
        Graphical();
        ~Graphical();

        sf::RenderWindow *getWindow();
        std::vector<std::unique_ptr<Button>> &getButtons();
        void displayWindowContent(int scene);
        void manageButtonCallback(int scene, std::string &deckPath);
        void addButton(float x, float y, float width, float height, int scene, std::string text, std::function<std::string()> callback, std::string buttonText, sf::Color color);
        void addCard(std::string name, std::string texturePath);
        void changeBackgroundTexture(std::string texturePath);
        sf::Text &getSearchBarText() { return this->_searchBarText; }
        sf::RectangleShape &getSearchBar() { return this->_searchBar; }
        std::string toggleInfo();
        std::unique_ptr<Button> &getButtonByText(std::string text);
        void updateDropdownMenu(const std::vector<std::string>& suggestions);
        std::string suggestClicked(int x, int y);
        void setVisibleCard(std::string cardName, bool visible);
        void createDeck(std::vector<std::unique_ptr<ACard>> cartes);
    private:
        sf::RenderWindow *_window;
        std::vector<std::tuple<std::unique_ptr<sf::RectangleShape>, bool, std::string>> _rectangles;
        std::vector<std::unique_ptr<Button>> _buttons;
        sf::RectangleShape _background;
        sf::RectangleShape _searchBar;
        sf::Text _searchBarText;
        sf::Font _font;
        std::unique_ptr<sf::Texture> _backgroundTexture;
        sf::RectangleShape _infoView;
        bool _infoViewIsOpen = true;
        std::vector<std::unique_ptr<sf::Text>> _dropdownMenu;
};

#endif /* !GRAPHICAL_HPP_ */

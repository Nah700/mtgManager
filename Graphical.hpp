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
#include <set>

class Graphical {
    public:
        Graphical();
        ~Graphical();

        sf::RenderWindow *getWindow();
        std::vector<std::unique_ptr<Button>> &getButtons();
        void displayWindowContent(int scene, std::string &deckPath, ACard &card);
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
        void infoCardTexture(ACard *card);
        void initInfoItems();
        void displayLoadingBar(float progress);
        void initLoading();
        std::string addCardToBoard(std::string cardName);
        void dragDropCard(sf::Event event);
        void clickCardOnBoard(sf::Event event);
        void moveCardToBack(std::string cardName);
        void enableCardInfos(std::string cardName);
        std::string getActiveCard() { return this->_activeCard; }

        //new
        void initRules();
        void handleRuleSelection(int selectedIndex);

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
        sf::RectangleShape _infoView2;
        std::vector<sf::Text> _cardInfos;
        sf::RectangleShape _cardInfoView;
        bool _infoViewIsOpen = true;
        std::vector<std::unique_ptr<sf::Text>> _dropdownMenu;
        sf::RectangleShape _loadingBar;
        sf::RectangleShape _loadingBarProgress;
        sf::Text _loadingBarText;
        std::string _activeCard = "";
        bool _dragDrop = false;
        bool _cardEnlarged = false;
        sf::Vector2f _originalCardPosition;
        sf::Vector2f _originalCardSize;
        sf::RectangleShape _checkbox1, _checkbox2;
        bool _checkbox1Checked = false, _checkbox2Checked = false;

        //new
        sf::RectangleShape _helpMenu;
        sf::Text _helpMenuText;
        std::vector<std::pair<std::string, std::string>> _rules;
        bool _showRuleDetails; 
        sf::Text _selectedRuleText;
        int _selectedRuleIndex;
        std::vector<std::string> _ruleTitles;
        sf::Text _ruleDefinitionText;
        std::map<std::string, float> _cardRotations;
};

#endif /* !GRAPHICAL_HPP_ */

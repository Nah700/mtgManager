/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** ACard
*/

#include "ACard.hpp"

ACard::ACard(std::string name, std::string manaCost, std::string cardtype, std::string text, std::string url, std::pair<int, int> powerToughness)
{
    this->_name = name;
    this->_manaCost = setManaCost(manaCost);
    this->_cardType = setCardType(cardtype);
    this->_text = text;
    this->_texturePath = url;
    this->_powerToughness = powerToughness;

    this->_cardTypeString = cardtype;
}

std::string ACard::getCardText()
{
    return this->_text;
}

std::string ACard::getName()
{
    return this->_name;
}

std::unordered_map<ManaType, int> ACard::getManaCost()
{
    return this->_manaCost;
}

std::vector<CardType> ACard::getCardType()
{
    return this->_cardType;
}

std::string ACard::getCardTypeStringed()
{
    return this->_cardTypeString;
}

int ACard::getPower()
{
    return this->_powerToughness.first;
}

int ACard::getToughness()
{
    return this->_powerToughness.second;
}

std::unordered_map<ManaType, int> ACard::setManaCost(std::string cost)
{
    std::unordered_map<ManaType, int> manaCostMap = {
        {ManaType::WHITE, 0},
        {ManaType::BLUE, 0},
        {ManaType::BLACK, 0},
        {ManaType::RED, 0},
        {ManaType::GREEN, 0},
        {ManaType::COLORLESS, 0},
        {ManaType::GENERIC, 0}
    };

    std::regex regex(R"(\{([^\{\}]+)\})");
    auto words_begin = std::sregex_iterator(cost.begin(), cost.end(), regex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string token = match.str(1);

        if (token == "W") {
            manaCostMap[ManaType::WHITE]++;
        } else if (token == "U") {
            manaCostMap[ManaType::BLUE]++;
        } else if (token == "B") {
            manaCostMap[ManaType::BLACK]++;
        } else if (token == "R") {
            manaCostMap[ManaType::RED]++;
        } else if (token == "G") {
            manaCostMap[ManaType::GREEN]++;
        } else if (token == "C") {
            manaCostMap[ManaType::COLORLESS]++;
        } else if (token == "X") {
            manaCostMap[ManaType::GENERIC]++;
        } else {
            try {
                int genericCost = std::stoi(token);
                manaCostMap[ManaType::GENERIC] += genericCost;
            } catch (const std::invalid_argument& e) {
                throw std::invalid_argument("Invalid mana cost: " + token);
            }
        }
    }

    return manaCostMap;
}

std::vector<CardType> ACard::setCardType(std::string type)
{
    std::vector<CardType> cardTypes;
    std::transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (type.find("creature") != std::string::npos) {
        cardTypes.push_back(CardType::CREATURE);
    }
    if (type.find("instant") != std::string::npos) {
        cardTypes.push_back(CardType::INSTANT);
    }
    if (type.find("sorcery") != std::string::npos) {
        cardTypes.push_back(CardType::SORCERY);
    }
    if (type.find("enchantment") != std::string::npos) {
        cardTypes.push_back(CardType::ENCHANTMENT);
    }
    if (type.find("artifact") != std::string::npos) {
        cardTypes.push_back(CardType::ARTIFACT);
    }
    if (type.find("planeswalker") != std::string::npos) {
        cardTypes.push_back(CardType::PLANESWALKER);
    }
    if (type.find("land") != std::string::npos) {
        cardTypes.push_back(CardType::LAND);
    }
    if (type.find("battle") != std::string::npos) {
        cardTypes.push_back(CardType::BATTLE);
    }

    if (cardTypes.empty()) {
        throw std::invalid_argument("Invalid card type: " + type);
    }

    return cardTypes;
}

std::string ACard::getTexturePath()
{
    return this->_texturePath;
}

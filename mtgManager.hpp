/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** mtgManager
*/

#ifndef MTGMANAGER_HPP_
#define MTGMANAGER_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <curl/curl.h>
#include <sstream>
#include <curl/curl.h>
//#include <jsoncpp/json/json.h>
#include <json/json.h>

enum ManaType {
    WHITE,
    BLUE,
    BLACK,
    RED,
    GREEN,
    COLORLESS
};

enum CardType {
    CREATURE,
    INSTANT,
    SORCERY,
    ENCHANTMENT,
    ARTIFACT,
    PLANESWALKER,
    LAND,
    BATTLE
};

std::string openFileExplorer();

#endif /* !MTGMANAGER_HPP_ */

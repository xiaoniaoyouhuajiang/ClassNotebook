//
// Created by Alex on 30.04.2020.
//

#include "GameLoader.h"

GameLoader::GameLoader(std::string path) : path(path) {}

GameLoader::~GameLoader() {
    if (fin.is_open()) {
        fin.close();
    }
}


void GameLoader::open() {
    fin.open(path);
}

void GameLoader::close() {
    fin.close();
}

void GameLoader::loadUnitsFromFile(int *numberInArray, std::string *type, int *x, int *y, int *health,
                                   int *maxHealth, int *armor, int *maxArmor, int *damage,
                                   int *attackBonus) {

    fin.ignore(6) >> *numberInArray;
    fin.ignore(7) >> *type;
    fin.ignore(4) >> *x;
    fin.ignore(4) >> *y;
    fin.ignore(7) >> *health;
    fin.ignore(10) >> *maxHealth;
    fin.ignore(6) >> *armor;
    fin.ignore(9) >> *maxArmor;
    fin.ignore(7) >> *damage;
    fin.ignore(12) >> *attackBonus;
    fin.ignore(2);
}

void GameLoader::loadCountUnits(int *count) {
    fin.ignore(11) >> *count;
    fin.ignore(2);
}

void GameLoader::loadBaseFromFile(int *x, int *y, int *maxCountUnits, int *health, int *money) {
    fin.ignore(14);
    fin.ignore(4) >> *x;
    fin.ignore(4) >> *y;
    fin.ignore(15) >> *maxCountUnits;
    fin.ignore(9) >> *health;
    fin.ignore(8) >> *money;
}

void GameLoader::loadNeutralObjects(std::string *type, bool *isActive, int *count, std::string *adress) {

    fin >> *type;
    fin.ignore(9) >> *isActive;
    fin.ignore(17) >> *count;
    if (*type == "GoldGenerator" || *type == "Village") {
        fin.ignore(14) >> *adress;
    }
}

void GameLoader::loadOrder(int *order) {
    fin.ignore(7) >> *order;
}

bool GameLoader::check() {

    int x;
    std::string string;



    if (!checkGamerSuper()) return false;
    // fin >> string;
    if (!checkGamerSuper()) return false;

    for (int i = 0; i < 6; ++i) {
        if (!checkNeutralObject()) return false;
    }

    fin >> string;

    if (string != "Order") return false;

    fin >> x;

    if (x != 1 && x != 2) return false;


    return true;
}

bool GameLoader::checkGame() {
    int x;
    std::string string;
    fin >> string;
    if (string != "Gamer") return false;
    fin >> x;
    if (x != 1 && x != 2) return false;
    return true;
}

bool GameLoader::checkBase() {
    int x;
    std::string string;

    fin >> string;
    if (string != "Base") return false;
    fin >> string;

    if (string != "x") return false;
    fin >> string;
    if (string != ":") return false;

    fin >> x;
    if (x < 0 || x > 9) return false;
    fin >> string;
    if (string != "y") return false;
    fin >> string;
    if (string != ":") return false;

    fin >> x;
    if (x < 0 || x > 4) return false;

    fin >> string;
    if (string != "maxCountUnit") return false;

    fin >> string;
    if (string != ":") return false;

    fin >> x;
    if (x < 0 || x > 10) return false;

    fin >> string;
    if (string != "health") return false;

    fin >> string;
    if (string != ":") return false;

    fin >> x;

    fin >> string;
    if (string != "money") return false;

    fin >> string;
    if (string != ":") return false;

    fin >> x;


    return true;
}

bool GameLoader::checkUnit() {
    int x;
    std::string string;

    fin >> string;
    if (string != "Unit") return false;
    fin >> string;
    /* if (string != "#") return false;
     fin >> x;
     fin >> string;*/
    fin >> string;
    if (string != "Type") return false;
    fin >> string;
    if (string != ":") return false;

    fin >> string;
    if (string != "King" && string != "Knight" && string != "Archer" &&
        string != "Magician" && string != "Spearmen" && string != "Swordmen")
        return false;

    fin >> string;
    if (string != "x") return false;
    fin >> string;
    if (string != ":") return false;

    fin >> x;
    if (x < 0 || x > 9) return false;
    fin >> string;
    if (string != "y") return false;
    fin >> string;
    if (string != ":") return false;

    fin >> x;
    if (x < 0 || x > 4) return false;

    fin >> string;
    if (string != "Health") return false;
    fin >> x;

    fin >> string;
    if (string != "MaxHealth") return false;
    fin >> x;

    fin >> string;
    if (string != "Armor") return false;
    fin >> x;

    fin >> string;
    if (string != "MaxArmor") return false;
    fin >> x;

    fin >> string;
    if (string != "Damage") return false;
    fin >> x;

    fin >> string;
    if (string != "AttackBonus") return false;
    fin >> x;

    return true;
}

bool GameLoader::checkGamerSuper() {
    int x;
    std::string string;
    if (!checkGame()) return false;
    if (!checkBase()) return false;
    fin >> string;
    if (string != "CountUits") return false;
    fin >> x;
    if (x < 0 || x > 10) return false;
    for (int i = 0; i < x; ++i) {
        if (!checkUnit()) return false;
    }
    return true;
}

bool GameLoader::checkNeutralObject() {
    std::string string;
    std::string string2;

    fin >> string;
    string2 = string;
    if (string != "HealthGenerator" && string != "ArmorGenerator" &&
        string != "GoldGenerator" && string != "Village")
        return false;
    fin >> string;
    if (string != "Active") return false;
    fin >> string;
    fin >> string;
    if (string != "CountGameMoves") return false;
    fin >> string;
    if (string2 == "GoldGenerator" || string2 == "Village") {
        fin >> string;
        if (string != "AddressMoney:") return false;
        fin >> string;
        if (string != "none" && string != "base1" && string != "base2") return false;
    }

    return true;
}

//
// Created by Alex on 01.05.2020.
//

#include "Gamer.h"

Gamer::Gamer(Field *field, Logger *logger, int xPositionBase, int yPositionBase, GameSaver *gameSaver,
             GameLoader *gameLoader,int number) {
    Gamer::number = number;
    Gamer::field = field;
    Gamer::logger = logger;
    Gamer::units = new Unit *[10];
    Gamer::base = new Base(units, xPositionBase, yPositionBase, 10, field,100,100);
    field->setBase(xPositionBase, yPositionBase, base);
    widthField = field->getWidth();
    heightField = field->getHeight();
    Gamer::gameSaver = gameSaver;
    Gamer::gameLoader = gameLoader;
}

Gamer::~Gamer() {
    int countUnits = base->getCountUnits();
    for (int i = 0; i < countUnits; ++i) {

        bool is = true;

        for (int num : base->vectorDeleteUnits) {
            if (i == num) {
                is = false;
                break;
            }
        }

        if (is) {
            delete (units[i]);
        }

    }
    delete (units);
    delete (base);
}

void Gamer::addSwordsmen(int x, int y) {
    if (x >= 0 && x < widthField && y >= 0 && y < heightField) {
        base->addSwordsmen(x, y);
        logger->logAddSwordsmen(x, y);
    }
}

void Gamer::addSpearmen(int x, int y) {
    if (x >= 0 && x < widthField && y >= 0 && y < heightField) {
        base->addSpearmen(x, y);
        logger->logAddSpearmen(x, y);
    }
}

void Gamer::addArcher(int x, int y) {
    if (x >= 0 && x < widthField && y >= 0 && y < heightField) {
        base->addArcher(x, y);
        logger->logAddArcher(x, y);
    }
}

void Gamer::addMagician(int x, int y) {
    if (x >= 0 && x < widthField && y >= 0 && y < heightField) {
        base->addMagician(x, y);
        logger->logAddMagician(x, y);
    }
}

void Gamer::addKing(int x, int y) {
    if (x >= 0 && x < widthField && y >= 0 && y < heightField) {
        base->addKing(x, y);
        logger->logAddKing(x, y);
    }
}

void Gamer::addKnight(int x, int y) {
    if (x >= 0 && x < widthField && y >= 0 && y < heightField) {
        base->addKnight(x, y);
        logger->logAddKnight(x, y);
    }
}

void Gamer::loadGamerState() {
    prepareForLoad();

    int count;
    gameLoader->loadCountUnits(&count);

    int numberInArray;
    std::string type;
    int x;
    int y;
    int health;
    int maxHealth;
    int armor;
    int maxArmor;
    int damage;
    int attackBonus;



    for (int i = 0; i < count; ++i) {
        gameLoader->loadUnitsFromFile(&numberInArray, &type, &x, &y, &health, &maxHealth, &armor, &maxArmor,
                                      &damage, &attackBonus);
        logger->logLoadUnit(x, y, type, health, maxHealth, armor, maxArmor, damage, attackBonus);
        if (type == "Archer") {
            base->loadArcher(x, y, i, health, armor, damage, attackBonus);
        } else if (type == "Magician") {
            base->loadArcher(x, y, i, health, armor, damage, attackBonus);
        } else if (type == "King") {
            base->loadKing(x, y, i, health, armor, damage, attackBonus);
        } else if (type == "Knight") {
            base->loadKnight(x, y, i, health, armor, damage, attackBonus);
        } else if (type == "Swordsmen") {
            base->loadSworsmen(x, y, i, health, armor, damage, attackBonus);
        } else if (type == "Spearmen") {
            base->loadSpearmen(x, y, i, health, armor, damage, attackBonus);
        }
    }
}

void Gamer::saveGamerState() {

    gameSaver->printInSaveFile("Gamer " + std::to_string(number) + '\n');
    gameSaver->printInSaveFile(base->getInformationAboutBase());
    gameSaver->printInSaveFile(getInfromationAboutUnitsForSave());
}

std::string Gamer::getInfromationAboutUnitsForSave() {

    std::string informationAboutUnits;

    informationAboutUnits.append("CountUits " + std::to_string(base->getCountUnitsInGame()) + "\n\n");

    int b = base->getCountUnits();
    for (int i = 0; i < b; ++i) {
        bool is = true;

        for (int num : base->vectorDeleteUnits) {
            if (i == num) {
                is = false;
                break;
            }
        }

        if (is) {
            informationAboutUnits.append(units[i]->getInformationAboutUnit());
        }
    }

    return informationAboutUnits;
}

int Gamer::getInformationAboutMoney() {
    return base->getMoney();
}

int Gamer::getInformationAboutBaseHealth() {
    return base->getHealthBase();
}

void Gamer::prepareForLoad() {
    int b = base->getCountUnits();
    for (int i = 0; i < b; ++i) {

        bool is = true;

        for (int num : base->vectorDeleteUnits) {
            if (i == num) {
                is = false;
                break;
            }
        }

        if (is) {
            delete (units[i]);
        }

    }
    delete (units);
    delete(base);

    Gamer::units = new Unit *[10];

    int xPositionBase;
    int yPositionBase;
    int countMaxUnits;
    int health;
    int money;

    gameLoader->loadBaseFromFile(&xPositionBase,&yPositionBase,&countMaxUnits,&health,&money);
    Gamer::base = new Base(units, xPositionBase, yPositionBase, 10, field,health,money);
    field->setBase(xPositionBase, yPositionBase, base);

}

int *Gamer::getMoneyAdress() {
    return base->getMoneyAdresse();
}

//
// Created by Alex on 22.03.2020.
//

#include "Game.h"
#include "../OtherClasses/Landscapes/ProxyLandscape.h"
//#include "../OtherClasses/NeutralObjects/Client.h"
#include "../Gamer/Gamer.h"
#include "../OtherClasses/NeutralObjects/Generators/HealthGenerator.h"
#include "../OtherClasses/NeutralObjects/Generators/ArmorGenerator.h"
#include "../OtherClasses/NeutralObjects/Generators/GoldGenerator.h"
#include "../OtherClasses/NeutralObjects/Village/Village.h"



//#include "../OtherClasses/NeutralObjects/Client.h"

Game::Game() {


    gameLoader = new GameLoader("C:\\Users\\Alex\\Desktop\\saver_game.txt");
    gameSaver = new GameSaver("C:\\Users\\Alex\\Desktop\\saver_game.txt");
    Game::field = new Field(widthField, heightField, 10);
    Game::neutralObjects = new NeutralObject *[6];
    setNeutralObject();
    gamer1 = new Gamer(field, &logger, 1, 1, gameSaver, gameLoader, 1);
    gamer2 = new Gamer(field, &logger, 8, 3, gameSaver, gameLoader, 2);

}


void Game::setNeutralObject() {
    neutralObjects[0] = new HealthGenerator;
    neutralObjects[1] = new ArmorGenerator;
    neutralObjects[2] = new GoldGenerator;
    neutralObjects[3] = new GoldGenerator;
    neutralObjects[4] = new Village;
    neutralObjects[5] = new Village;

    field->getCell(3, 1)->setNeutralObject(neutralObjects[0]);
    field->getCell(6, 3)->setNeutralObject(neutralObjects[1]);
    field->getCell(0, 3)->setNeutralObject(neutralObjects[2]);
    field->getCell(9, 1)->setNeutralObject(neutralObjects[3]);
    field->getCell(1, 3)->setNeutralObject(neutralObjects[4]);
    field->getCell(8, 1)->setNeutralObject(neutralObjects[5]);

}

Game::~Game() {

    delete (field);
    delete (gameLoader);
    delete (gamer1);
    delete (gamer2);
}

void Game::getInformationAboutEnvironment(int *array, int x, int y) {
    array[0] = 0;
    array[1] = 0;
    array[2] = 0;
    array[3] = 0;

    int leftCellX = x - 1;
    int rightCellX = x + 1;
    int topCellY = y + 1;
    int bottomCellY = y - 1;

    /* GameCell *gameCell = field->getCell(x, y);
     Landscape *landscape = gameCell->getLanscape();
     bool sds = landscape->getInformationAboutLandscape();*/

    if (leftCellX >= 0 && leftCellX < field->getWidth()) {

        if (field->getCell(leftCellX, y)->getLanscape()->getInformationAboutLandscape()) {
            array[0] = 1;
            if (field->getCell(leftCellX, y)->getUnit() != nullptr) {
                array[0] = 2;
            }
        }
    }

    if (rightCellX >= 0 && rightCellX < field->getWidth()) {
        if (field->getCell(rightCellX, y)->getLanscape()->getInformationAboutLandscape()) {
            array[1] = 1;
            if (field->getCell(rightCellX, y)->getUnit() != nullptr) {
                array[1] = 2;
            }
        }
    }

    if (topCellY >= 0 && topCellY < field->getHeight()) {
        if (field->getCell(x, topCellY)->getLanscape()->getInformationAboutLandscape()) {
            array[2] = 1;
            if (field->getCell(x, topCellY)->getUnit() != nullptr) {
                array[2] = 2;
            }
        }
    }

    if (bottomCellY >= 0 && bottomCellY < field->getHeight()) {
        if (field->getCell(x, bottomCellY)->getLanscape()->getInformationAboutLandscape()) {
            array[3] = 1;
            if (field->getCell(x, bottomCellY)->getUnit() != nullptr) {
                array[3] = 2;
            }
        }
    }
}

void Game::updateUnitPosition(int lastX, int lastY, int newX, int newY) {
    field->updateUnitPosition(lastX, lastY, newX, newY);
    logger.logUpdatePosition(lastX, lastY, newX, newY);

    ProxyLandscape proxyLandscape(field->getCell(newX, newY)->getLanscape());
    proxyLandscape.setBonus(field->getCell(newX, newY)->getUnit());

    Client client;
    client.setStrategy(field->getCell(newX, newY)->getNeutralObject());
    client.useStrategy(field->getCell(newX, newY)->getUnit());
    field->getCell(newX, newY)->getUnit()->setX(newX);
    field->getCell(newX, newY)->getUnit()->setY(newY);
}

bool Game::attackUnit(int xPositionUnit1, int yPositionUnit1, int xPositionUnit2, int yPositionUnit2) {
    bool isAlive = true;

    Unit *unit1 = field->getCell(xPositionUnit1, yPositionUnit1)->getUnit();
    Unit *unit2 = field->getCell(xPositionUnit2, yPositionUnit2)->getUnit();


    unit1->attack(unit2);
    logger.logAttackUnit(xPositionUnit1, yPositionUnit1, xPositionUnit2, yPositionUnit2);

    if (unit2->getHealth() <= 0) {
        logger.logUnitDie(xPositionUnit2, yPositionUnit2);
        delete unit2;
        field->getCell(xPositionUnit2, yPositionUnit2)->setUnit(nullptr);
        isAlive = false;
    }

    return isAlive;
}

void Game::saveNeutralObject() {
    std::string inf;
    inf.append(neutralObjects[0]->getInformationAboutNeutralObject(gamer1->getMoneyAdress(), gamer2->getMoneyAdress()));
    inf.append(neutralObjects[1]->getInformationAboutNeutralObject(gamer1->getMoneyAdress(), gamer2->getMoneyAdress()));
    inf.append(neutralObjects[2]->getInformationAboutNeutralObject(gamer1->getMoneyAdress(), gamer2->getMoneyAdress()));
    inf.append(neutralObjects[3]->getInformationAboutNeutralObject(gamer1->getMoneyAdress(), gamer2->getMoneyAdress()));
    inf.append(neutralObjects[4]->getInformationAboutNeutralObject(gamer1->getMoneyAdress(), gamer2->getMoneyAdress()));
    inf.append(neutralObjects[5]->getInformationAboutNeutralObject(gamer1->getMoneyAdress(), gamer2->getMoneyAdress()));

    gameSaver->printInSaveFile(inf);

}

void Game::saveGamers() {
    gamer1->saveGamerState();
    gamer2->saveGamerState();
}

void Game::saveState() {
    gameSaver->open();
    saveGamers();
    saveNeutralObject();
    saveOrder();
    gameSaver->close();

}

void Game::loadState() {
    logger.logStartLoad();
    if (checkFile()) {
        logger.logLoadCorrect();
        gameLoader->open();
        field->resetUnits();
        loadGamers();
        loadNeutralObject();
        loadOrder();
        gameLoader->close();
    } else{
        logger.logLoadNotCorrect();
    }
    logger.logEndLoad();
}

void Game::loadGamers() {
    gamer1->loadGamerState();
    gamer2->loadGamerState();
}

void Game::loadNeutralObject() {
    std::string type;
    bool isActive;
    int count;
    std::string adress;


    for (int i = 0; i < 6; ++i) {
        gameLoader->loadNeutralObjects(&type, &isActive, &count, &adress);
        neutralObjects[i]->setIsActive(isActive);
        neutralObjects[i]->setCountGameMoves(count);
        if (type == "GoldGenerator" || type == "Village") {
            if (adress == "none") {
                if (type == "GoldGenerator") {
                    dynamic_cast<GoldGenerator *>(neutralObjects[i])->setAddressMoney(nullptr);
                } else if (type == "Village") {
                    dynamic_cast<Village *>(neutralObjects[i])->setAddressMoney(nullptr);
                }
            } else if (adress == "base1") {
                if (type == "GoldGenerator") {
                    dynamic_cast<GoldGenerator *>(neutralObjects[i])->setAddressMoney(gamer1->getMoneyAdress());
                } else if (type == "Village") {
                    dynamic_cast<Village *>(neutralObjects[i])->setAddressMoney(gamer1->getMoneyAdress());
                }
            } else if (adress == "base2") {
                if (type == "GoldGenerator") {
                    dynamic_cast<GoldGenerator *>(neutralObjects[i])->setAddressMoney(gamer2->getMoneyAdress());
                } else if (type == "Village") {
                    dynamic_cast<Village *>(neutralObjects[i])->setAddressMoney(gamer2->getMoneyAdress());
                }
            }
        }
    }
}

int Game::getOrder() const {
    return order;
}

void Game::setOrder(int order) {
    Game::order = order;
}

void Game::loadOrder() {
    gameLoader->loadOrder(&order);
}

void Game::saveOrder() {
    gameSaver->printInSaveFile("Order " + std::to_string(order));
}

bool Game::checkFile() {
    gameLoader->open();
    bool result = gameLoader->check();
    gameLoader->close();
    return result;
}





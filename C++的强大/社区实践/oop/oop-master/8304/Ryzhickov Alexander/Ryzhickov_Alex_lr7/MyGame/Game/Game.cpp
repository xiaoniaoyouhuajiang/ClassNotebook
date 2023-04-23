//
// Created by Alex on 22.03.2020.
//

#include <iostream>
#include "Game.h"
#include "../OtherClasses/Landscapes/ProxyLandscape.h"
//#include "../OtherClasses/NeutralObjects/Client.h"
#include "../Gamer/Gamer.h"
#include "../OtherClasses/NeutralObjects/Generators/HealthGenerator.h"
#include "../OtherClasses/NeutralObjects/Generators/ArmorGenerator.h"
#include "../OtherClasses/NeutralObjects/Generators/GoldGenerator.h"
#include "../OtherClasses/NeutralObjects/Village/Village.h"
#include "../Rules/FirstRule.h"
#include "../Rules/SecondRule.h"
#include "../Exceptions/UpdateUnitPositionExeption/UpdateUnitPositionException.h"
#include "../Exceptions/UpdateUnitPositionExeption/CellNotFreeException.h"
#include "../Exceptions/UpdateUnitPositionExeption/CellEmptyException.h"

using namespace Logging;
using namespace GameUnit;
using namespace MyGameException;
//#include "../OtherClasses/NeutralObjects/Client.h"
namespace MyGame {
    Game::Game() {

        Game::rule = new FirstRule;
        gameLoader = new GameLoader("C:\\Users\\Alex\\Desktop\\saver_game.txt");
        gameSaver = new GameSaver("C:\\Users\\Alex\\Desktop\\saver_game.txt");
        Game::field = new Field(widthField, heightField, 10);
        Game::neutralObjects = new NeutralObject *[6];
        setNeutralObject();
        initGame();

    }

    void Game::initGame() {
        order = rule->getOrder();
        gamer1 = new Gamer(field, &logger, 1, 1, gameSaver, gameLoader, 1, rule->getStartMoney());
        gamer2 = new Gamer(field, &logger, 8, 3, gameSaver, gameLoader, 2, rule->getStartMoney());

        /* int array[6] = {0,0,0,0,0,0};
         rule->getStartUnitPack(array);
         if(array[0]==1){
             gamer1->addSpearmen(2,1);
             gamer2->addSpearmen(7,3);
         }
         if(array[1]==1){
             gamer1->addSwordsmen(2,2);
             gamer2->addSwordsmen(7,2);
         }
         if(array[2]==1){
             gamer1->addKing(1,0);
             gamer2->addKing(8,4);
         }
         if(array[3]==1){
             gamer1->addKnight(0,1);
             gamer2->addKnight(9,3);
         }
         if(array[4]==1){
             gamer1->addArcher(0,0);
             gamer2->addArcher(9,4);
         }
         if(array[5]==1){
             gamer1->addMagician(1,2);
             gamer2->addMagician(8,2);
         }*/

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
        try {
            field->updateUnitPosition(lastX, lastY, newX, newY);
            logger.logUpdatePosition(lastX, lastY, newX, newY);


            ProxyLandscape proxyLandscape(field->getCell(newX, newY)->getLanscape());
            proxyLandscape.setBonus(field->getCell(newX, newY)->getUnit());

            Client client;
            client.setStrategy(field->getCell(newX, newY)->getNeutralObject());
            client.useStrategy(field->getCell(newX, newY)->getUnit());
            field->getCell(newX, newY)->getUnit()->setX(newX);
            field->getCell(newX, newY)->getUnit()->setY(newY);

            if (dynamic_cast<FirstRule *>(rule) != nullptr) {
                if (newX == 1 && newY == 1) {
                    if (dynamic_cast<FirstRule *>(rule)->checkEndGame(field->getCell(1, 1)->getUnit()->getMoney(),
                                                                      gamer2->getMoneyAdress())) {
                        logger.logSecondGamerWin();
                    }
                }
                if (newX == 8 && newY == 3) {
                    if (dynamic_cast<FirstRule *>(rule)->checkEndGame(field->getCell(8, 3)->getUnit()->getMoney(),
                                                                      gamer1->getMoneyAdress())) {
                        logger.logFirstGamerWin();
                    }
                }
            }
        } catch (UpdateUnitPositionException &ex) {
            std::cout << ex.what();
        } catch (CellNotFreeException &ex) {
            std::cout << ex.what();
        } catch (CellEmptyException &ex) {
            std::cout << ex.what();
        }
    }

    bool Game::attackUnit(int xPositionUnit1, int yPositionUnit1, int xPositionUnit2, int yPositionUnit2) {
        bool isAlive = true;

        try {

            checkAttack(xPositionUnit1, yPositionUnit1, xPositionUnit2, yPositionUnit2);
            GameUnit::Unit *unit1 = field->getCell(xPositionUnit1, yPositionUnit1)->getUnit();
            GameUnit::Unit *unit2 = field->getCell(xPositionUnit2, yPositionUnit2)->getUnit();


            unit1->attack(unit2);
            logger.logAttackUnit(xPositionUnit1, yPositionUnit1, xPositionUnit2, yPositionUnit2);

            if (unit2->getHealth() <= 0) {
                logger.logUnitDie(xPositionUnit2, yPositionUnit2);
                if (dynamic_cast<SecondRule *>(rule) != nullptr) {
                    if (dynamic_cast<SecondRule *>(rule)->checkEndGame(unit2, gamer1->getMoneyAdress())) {
                        logger.logSecondGamerWin();
                    }
                    if (dynamic_cast<SecondRule *>(rule)->checkEndGame(unit2, gamer2->getMoneyAdress())) {
                        logger.logFirstGamerWin();
                    }
                }
                delete unit2;
                field->getCell(xPositionUnit2, yPositionUnit2)->setUnit(nullptr);
                isAlive = false;
            }
        } catch (UpdateUnitPositionException &ex) {
            std::cout << "Error input data in attack method!\n";
            std::cout << ex.what();
        } catch (CellNotFreeException &ex) {
            std::cout << "Error input data in attack method!\n";
            std::cout << ex.what();
        } catch (CellEmptyException &ex) {
            std::cout << "Error input data in attack method!\n";
            std::cout << ex.what();
        }

        return isAlive;
    }

    void Game::saveNeutralObject() {
        std::string inf;
        inf.append(neutralObjects[0]->getInformationAboutNeutralObject(gamer1->getMoneyAdress(),
                                                                       gamer2->getMoneyAdress()));
        inf.append(neutralObjects[1]->getInformationAboutNeutralObject(gamer1->getMoneyAdress(),
                                                                       gamer2->getMoneyAdress()));
        inf.append(neutralObjects[2]->getInformationAboutNeutralObject(gamer1->getMoneyAdress(),
                                                                       gamer2->getMoneyAdress()));
        inf.append(neutralObjects[3]->getInformationAboutNeutralObject(gamer1->getMoneyAdress(),
                                                                       gamer2->getMoneyAdress()));
        inf.append(neutralObjects[4]->getInformationAboutNeutralObject(gamer1->getMoneyAdress(),
                                                                       gamer2->getMoneyAdress()));
        inf.append(neutralObjects[5]->getInformationAboutNeutralObject(gamer1->getMoneyAdress(),
                                                                       gamer2->getMoneyAdress()));

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
        } else {
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

    void Game::startNewGame() {
        delete (field);
        delete (gamer1);
        delete (gamer2);
        Game::field = new Field(widthField, heightField, 10);
        Game::neutralObjects = new NeutralObject *[6];
        setNeutralObject();
        initGame();
    }

    void Game::switchOrder() {
        if (order == 1) {
            order = 0;
        } else {
            if (order == 0) {
                order = 1;
            }
        }
    }

    Gamer *Game::getCurrentGamer() {
        if (order == 1) {
            return gamer1;
        }
        if (order == 0) {
            return gamer2;
        }
    }

    void Game::checkAttack(int xPositionUnit1, int yPositionUnit1, int xPositionUnit2, int yPositionUnit2) {
        if (xPositionUnit1 < 0 || xPositionUnit1 >= widthField) {
            throw UpdateUnitPositionException(xPositionUnit1, yPositionUnit1, widthField - 1, heightField - 1, 1);
        }
        if (yPositionUnit1 < 0 || yPositionUnit1 >= heightField) {
            throw UpdateUnitPositionException(xPositionUnit1, yPositionUnit1, widthField - 1, heightField - 1, 1);
        }
        if (xPositionUnit2 < 0 || xPositionUnit2 >= widthField) {
            throw UpdateUnitPositionException(xPositionUnit2, yPositionUnit2, widthField - 1, heightField - 1, 2);
        }
        if (yPositionUnit2 < 0 || yPositionUnit2 >= heightField) {
            throw UpdateUnitPositionException(xPositionUnit2, yPositionUnit2, widthField - 1, heightField - 1, 2);
        }

        if (field->getCell(xPositionUnit1, yPositionUnit1)->getUnit() == nullptr) {
            throw CellEmptyException(xPositionUnit1, yPositionUnit1);
        }

        if (field->getCell(xPositionUnit2, yPositionUnit2)->getUnit() == nullptr) {
            throw CellEmptyException(xPositionUnit2, yPositionUnit2);
        }
    }

    void Game::checkAddUnit(int x, int y) {
        if (x < 0 || x >= widthField) {
            throw UpdateUnitPositionException(x, y, widthField - 1, heightField - 1, 1);
        }
        if (y < 0 || y >= heightField) {
            throw UpdateUnitPositionException(x, y, widthField - 1, heightField - 1, 1);
        }
    }

}




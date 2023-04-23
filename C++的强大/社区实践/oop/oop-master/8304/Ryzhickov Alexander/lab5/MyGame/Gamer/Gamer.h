//
// Created by Alex on 01.05.2020.
//

#ifndef GAME_GAMER_H
#define GAME_GAMER_H


#include "../OtherClasses/Base/Base.h"
#include "../OtherClasses/Field/Field.h"
#include "../Logging/Logger/Logger.h"
#include "../SaveGame/GameSaver.h"
#include "../SaveGame/GameLoader.h"

class Gamer {
private:
    int widthField;
    int heightField;
    Base *base;
    Unit **units;
    Field *field;
    Logger *logger;
    GameSaver *gameSaver;
    GameLoader *gameLoader;
    int number;
public:
    Gamer(Field *field, Logger *logger,int xPositionBase, int yPositionBase, GameSaver *gameSaver,
          GameLoader *gameLoader,int number);
    ~Gamer();

    void addSwordsmen(int x, int y);

    void addSpearmen(int x, int y);

    void addArcher(int x, int y);

    void addMagician(int x, int y);

    void addKnight(int x, int y);

    void addKing(int x, int y);

    void loadGamerState();

    void saveGamerState();

    int *getMoneyAdress();


    std::string getInfromationAboutUnitsForSave();

    int getInformationAboutMoney();

    int getInformationAboutBaseHealth();

    void prepareForLoad();
};


#endif //GAME_GAMER_H

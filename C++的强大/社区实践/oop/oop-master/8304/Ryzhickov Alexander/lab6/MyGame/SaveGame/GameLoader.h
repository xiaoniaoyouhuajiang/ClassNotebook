//
// Created by Alex on 30.04.2020.
//

#ifndef GAME_GAMELOADER_H
#define GAME_GAMELOADER_H

#include <string>
#include <fstream>

class GameLoader {
private:
    std::string path;
    std::ifstream fin;
public:
    GameLoader(std::string path);
    ~GameLoader();
    void loadBaseFromFile(int *x, int *y,int *maxCountUnits, int *health, int *money);
    void loadUnitsFromFile(int *numberInArray, std::string *type, int *x, int *y, int *health,
                           int *maxHealth, int *armor, int *maxArmor, int *damage,
                           int *attackBonus);
    void loadCountUnits(int *count);
    void loadOrder(int *order);
    void open();
    void close();
    void loadNeutralObjects(std::string *type, bool *isActive, int *count, std::string *adress);
    bool check();

private:
    bool checkGame();
    bool checkBase();
    bool checkUnit();
    bool checkGamerSuper();
    bool checkNeutralObject();
};


#endif //GAME_GAMELOADER_H

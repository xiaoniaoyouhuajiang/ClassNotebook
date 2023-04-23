//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_GAMERULES_H
#define OOPROJECT_GAMERULES_H

#include <utility>

enum class WinCondition{
    BaseDestriyed,
    UnitsDead
};

struct GameRules {
    bool firstA;
    int width;
    int height;
    std::pair<int,int> initAPos;
    std::pair<int,int> initBPos;
    bool multiplayer;
    WinCondition winCondition=WinCondition ::BaseDestriyed;
};


#endif //OOPROJECT_GAMERULES_H

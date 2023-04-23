//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_ARMORGENERATOR_H
#define GAME_ARMORGENERATOR_H


#include "../NeutralObject.h"

class ArmorGenerator: public NeutralObject {
private:
    unsigned armorPoints = 50;
public:
    ArmorGenerator();
    void operator[](unsigned *something) override ;
    void makeGameMove() override ;
};


#endif //GAME_ARMORGENERATOR_H

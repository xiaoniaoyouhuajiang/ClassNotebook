//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_GOLDGENERATOR_H
#define GAME_GOLDGENERATOR_H


#include "../NeutralObject.h"

class GoldGenerator: public NeutralObject {
private:
    unsigned goldPoints = 50;
    unsigned *addressMoney = nullptr;
public:
    GoldGenerator();
    void operator[](unsigned *something) override ;
    void makeGameMove() override ;
};


#endif //GAME_GOLDGENERATOR_H

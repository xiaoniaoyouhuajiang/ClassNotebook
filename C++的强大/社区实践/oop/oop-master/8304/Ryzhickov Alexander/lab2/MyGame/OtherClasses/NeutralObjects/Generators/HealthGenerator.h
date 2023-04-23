//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_HEALTHGENERATOR_H
#define GAME_HEALTHGENERATOR_H


#include "../NeutralObject.h"

class HealthGenerator: public NeutralObject {
private:
    unsigned healthPoints = 50;
public:
    HealthGenerator();
    void operator[](unsigned *something) override ;
    void makeGameMove() override ;
};


#endif //GAME_HEALTHGENERATOR_H

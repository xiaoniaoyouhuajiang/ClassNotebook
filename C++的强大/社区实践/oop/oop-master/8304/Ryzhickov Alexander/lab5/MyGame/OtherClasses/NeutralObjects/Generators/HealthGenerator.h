//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_HEALTHGENERATOR_H
#define GAME_HEALTHGENERATOR_H


#include "../NeutralObject.h"

class HealthGenerator: public NeutralObject {
private:
    int healthPoints = 50;
public:
    HealthGenerator();
    void operator[](int *something) override ;
    void makeGameMove() override ;
    std::string getInformationAboutNeutralObject(int *adress1, int *adress2) override ;

};


#endif //GAME_HEALTHGENERATOR_H

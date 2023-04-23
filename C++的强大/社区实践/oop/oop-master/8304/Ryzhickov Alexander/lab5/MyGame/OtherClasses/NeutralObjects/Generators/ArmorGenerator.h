//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_ARMORGENERATOR_H
#define GAME_ARMORGENERATOR_H


#include "../NeutralObject.h"

class ArmorGenerator: public NeutralObject {
private:
    int armorPoints = 50;
public:
    ArmorGenerator();
    void operator[](int *something) override ;
    void makeGameMove() override ;
    std::string getInformationAboutNeutralObject(int *adress1, int *adress2) override ;
};


#endif //GAME_ARMORGENERATOR_H

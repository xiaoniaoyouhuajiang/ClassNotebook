//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_GOLDGENERATOR_H
#define GAME_GOLDGENERATOR_H


#include "../NeutralObject.h"

class GoldGenerator: public NeutralObject {
private:
    int goldPoints = 50;
    int *addressMoney = nullptr;
public:
    void setAddressMoney(int *addressMoney);

public:
    GoldGenerator();
    void operator[](int *something) override ;
    void makeGameMove() override ;
    std::string getInformationAboutNeutralObject(int *adress1, int *adress2) override ;
};


#endif //GAME_GOLDGENERATOR_H

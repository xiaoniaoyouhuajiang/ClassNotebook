//
// Created by Alex on 21.03.2020.
//

#include "ArmorGenerator.h"

ArmorGenerator::ArmorGenerator() {
    isActive = true;
    countGameMoves = 0;
}

void ArmorGenerator::operator[](int *something) {
    if(isActive) {
        *something = *something + armorPoints;
        isActive = false;
    }
}

void ArmorGenerator::makeGameMove() {
    if (countGameMoves == 3) {
        isActive = true;
        countGameMoves = 0;
    }
    if (!isActive) {
        countGameMoves++;
    }
}

std::string ArmorGenerator::getInformationAboutNeutralObject(int *adress1, int *adress2) {
    std::string inf;
    inf.append("ArmorGenerator\n");
    inf.append("Active :"+std::to_string(isActive)+'\n');
    inf.append("CountGameMoves :"+std::to_string(countGameMoves)+'\n');
    return inf;
}

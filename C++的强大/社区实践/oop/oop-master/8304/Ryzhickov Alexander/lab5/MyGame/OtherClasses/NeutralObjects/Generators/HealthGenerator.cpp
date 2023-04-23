//
// Created by Alex on 21.03.2020.
//

#include "HealthGenerator.h"

HealthGenerator::HealthGenerator() {
    isActive = true;
    countGameMoves = 0;
}

void HealthGenerator::operator[](int *something) {
    if(isActive) {
        *something = *something + healthPoints;
        isActive = false;
    }
}

void HealthGenerator::makeGameMove() {
    if (countGameMoves == 3) {
        isActive = true;
        countGameMoves = 0;
    }
    if (!isActive) {
        countGameMoves++;
    }
}

std::string HealthGenerator::getInformationAboutNeutralObject(int *adress1, int *adress2) {
    std::string inf;
    inf.append("HealthGenerator\n");
    inf.append("Active :"+std::to_string(isActive)+'\n');
    inf.append("CountGameMoves :"+std::to_string(countGameMoves)+'\n');
    return inf;
}

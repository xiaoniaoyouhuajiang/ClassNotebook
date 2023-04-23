//
// Created by Alex on 21.03.2020.
//

#include "ArmorGenerator.h"

ArmorGenerator::ArmorGenerator() {
    isActive = true;
    countGameMoves = 0;
}

void ArmorGenerator::operator[](unsigned *something) {
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

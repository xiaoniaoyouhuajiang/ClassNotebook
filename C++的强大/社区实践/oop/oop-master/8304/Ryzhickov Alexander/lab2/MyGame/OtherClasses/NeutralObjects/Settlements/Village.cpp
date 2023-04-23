//
// Created by Alex on 21.03.2020.
//

#include "Village.h"

Village::Village() {
    isActive = true;
    countGameMoves = 0;
}

void Village::operator[](unsigned *something) {
    addressMoney = something;
}

void Village::makeGameMove() {
    *addressMoney = *addressMoney + goldPoints;
}

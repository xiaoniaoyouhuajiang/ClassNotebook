//
// Created by Alex on 21.03.2020.
//

#include "GoldGenerator.h"

GoldGenerator::GoldGenerator() {
    isActive = true;
    countGameMoves = 0;
}

void GoldGenerator::operator[](int *something) {
    addressMoney = something;
}

void GoldGenerator::makeGameMove() {
    if (addressMoney != nullptr) {
        *addressMoney = *addressMoney + goldPoints;
    }
}

std::string GoldGenerator::getInformationAboutNeutralObject(int *adress1, int *adress2) {
    std::string inf;
    inf.append("GoldGenerator\n");
    inf.append("Active :"+std::to_string(isActive)+'\n');
    inf.append("CountGameMoves :"+std::to_string(countGameMoves)+'\n');
    if (addressMoney == nullptr){
        inf.append("AddressMoney: none\n");
    } else if (addressMoney == adress1){
        inf.append("AddressMoney: base1\n");
    } else if (addressMoney == adress2){
        inf.append("AddressMoney: base2\n");
    }
    return inf;
}

void GoldGenerator::setAddressMoney(int *addressMoney) {
    GoldGenerator::addressMoney = addressMoney;
}

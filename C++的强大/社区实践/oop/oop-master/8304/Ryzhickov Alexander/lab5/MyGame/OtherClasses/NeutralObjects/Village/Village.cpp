//
// Created by Alex on 21.03.2020.
//

#include "Village.h"

Village::Village() {
    isActive = true;
    countGameMoves = 0;
}

void Village::operator[](int *something) {
    addressMoney = something;
}

void Village::makeGameMove() {
    if (addressMoney != nullptr) {
        *addressMoney = *addressMoney + goldPoints;
    }
}

std::string Village::getInformationAboutNeutralObject(int *adress1, int *adress2) {
    std::string inf;
    inf.append("Village\n");
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

void Village::setAddressMoney(int *addressMoney) {
    Village::addressMoney = addressMoney;
}

//
// Created by Alex on 11.05.2020.
//

#include "SecondRule.h"
#include "../Units/Unit.h"
#include "../Units/HeavyInfantry/King.h"

void SecondRule::getStartUnitPack(int *arrayUnit) {
    arrayUnit[0]=0; //Spearmen
    arrayUnit[1]=0; //Swordmen
    arrayUnit[2]=1; //King
    arrayUnit[3]=0; //Knight
    arrayUnit[4]=0; //Archer
    arrayUnit[5]=0; //Magician
}

int SecondRule::getStartMoney() {
    return 1000;
}

bool SecondRule::checkEndGame(Unit *unit,int *adress1) {
    if(dynamic_cast<King *>(unit) != nullptr){
        if (unit->getMoney()==adress1){
            return true;
        }
    }

    return false;
}

int SecondRule::getOrder() {
    return 1;
}



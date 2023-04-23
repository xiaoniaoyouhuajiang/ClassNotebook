//
// Created by vlad on 02.06.2020.
//

#include "LightBase.h"

LightBase::LightBase():x(0), y(0), health(1), type('b'){}

int LightBase::CreateUnits() {
    int tmp = rand()%3;
    return tmp;
}

LightArcher LightBase::createLightArcher(){
    LightArcher la;
    return la;
}

LightCavalry LightBase::createLightCavalry(){
    LightCavalry lc;
    return lc;
}

LightInfantry LightBase::createLightInfantry(){
    LightInfantry li;
    return li;
}

int LightBase::checkBase() const{
    if (this->health <= 0)
        return 1;
}

void LightBase::getDamage(int attack) {
    this->health = this->health - attack;
}

int LightBase::ControlUnits(Field& field) {
    int count = 0;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++)
            if (field.field[i][j] == 'a' || field.field[i][j] == 'c' || field.field[i][j] == 'i')
                count++;
    }
    return count;
}


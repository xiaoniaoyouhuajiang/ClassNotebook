//
// Created by vlad on 01.06.2020.
//

#include "LightArmy.h"

LightCavalry::LightCavalry():type('c'), health(2), attack(3), armor(1), x(1), y(0){}
LightInfantry::LightInfantry():type('i'), health(2), attack(2), armor(1), x(0), y(1){}
LightArcher::LightArcher() : type('a'), health(3), attack(2), armor(0), x(1), y(1) {}

int LightCavalry::MoveUnits(int a, int b) {
    try {
        if((abs(this->x - a) > 2) || (abs(this->y - b) > 2))
            throw "You went too far";
        this->x = a;
        this->y = b;
    }
    catch (const char * exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
    return 0;
}

int LightInfantry::MoveUnits(int a, int b) {
    try {
        if((abs(this->x - a) > 1) || (abs(this->y - b) > 1))
            throw "You went too far";
        this->x = a;
        this->y = b;
    }
    catch (const char * exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
    return 0;
}

int LightArcher::MoveUnits(int a, int b) {
    try {
        if((abs(this->x - a) > 1) || (abs(this->y - b) > 1))
            throw "You went too far";
        this->x = a;
        this->y = b;
    }
    catch (const char * exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
    return 0;
}

int LightCavalry::AttackUnits(char** field, char choose){
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if (field[i][j] == choose){
                if (abs(x - i) <= 1) {
                    if (abs(y - j) <= 1)
                        return this->attack;
                }
            }
        }
    }
    return -1;
}

int LightInfantry::AttackUnits(char** field, char choose){
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if (field[i][j] == choose){
                if (abs(x - i) <= 1) {
                    if (abs(y - j) <= 1)
                        return this->attack;
                }
            }
        }
    }
    return -1;
}

int LightArcher::AttackUnits(char** field, char choose){
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if (field[i][j] == choose){
                if (abs(x - i) <= 10) {
                    if (abs(y - j) <= 10)
                        return this->attack;
                }
            }
        }
    }
    return -1;
}

void LightCavalry::getDamage(int att){
    if (att > this->armor)
        this->health = this->health -  (att - this->armor);
    if (this->health <= 0)
        this->type = '.';
}

void LightInfantry::getDamage(int att) {
    if (att > this->armor)
        this->health = this->health - (att - this->armor);
    if (this->health <= 0)
        this->type = '.';
}

void LightArcher::getDamage(int att) {
    if (att > this->armor)
        this->health = this->health - (att - this->armor);
    if (this->health <= 0)
        this->type = '.';
}

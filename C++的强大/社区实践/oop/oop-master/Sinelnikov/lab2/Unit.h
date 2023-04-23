//
// Created by max on 19.02.20.
//

#ifndef OOP_UNIT_H
#define OOP_UNIT_H

#include <iostream>
#include <string.h>

using std::string;
using std::cin;
using std::cout;
using std::pair;
using std::make_pair;

class Unit {
public:
    Unit()
    {

    }
    ~Unit()
    {

    }
    void operator = (const Unit &other){
        this->number_in_array = other.number_in_array;
        this->xp = other.xp;
        this->attack = other.attack;
        this->armour = other.armour;
        this->unit_id = other.unit_id;
        this->moral = other.moral;
        this->max_armour = other.max_armour;
        this->max_moral = other.max_moral;
        this->max_xp = other.max_xp;
    }
    void setParameters(int xp,int armour,int attack,string name_of_unit);
    virtual string getUnitType()=0;
    virtual int getMaxAttack() = 0;
    void printXp();
    void printArmour();
    void printAttack();
    void increaseXp(int amount);
    void increaseMoral(int amount);
    void decreaseXp(int amount);
    void decreaseMoral(int amount);
    void repairArmour();
    int getXp();
    int getArmour();
    int getAttack();
    int getMoral();
    int getMaxXp();
    int getMaxMoral();
    int getMaxArmour();
    void setMaxArmour(int armour);
    void cleanUnitMemory();
    void setId(int id);
    int getId();
    int getNumberInArray();
    void arrangeCavalryToIntantry();
    void setNumberInArray(int index);

private:
    int xp;
    int moral = 10;
    int max_xp = 10;
    int max_moral = 10;
    int armour;
    int attack;
    int unit_id;
    int max_armour;
    int number_in_array = 0;
    string name_of_unit;
};

#endif //OOP_UNIT_H
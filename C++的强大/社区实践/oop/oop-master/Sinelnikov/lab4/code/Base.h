//
// Created by max on 05.03.20.
//

#ifndef OOP_BASE_H
#define OOP_BASE_H

#include "Archer.h"
#include "Infantry.h"
#include "Cavalry.h"
#include "Object.h"

class Field;
class Cell;

class Base : public Object{
    int basexp;
    int number_of_units;
    int max_number_of_units;
public:
    Base(int x,int y,int id) : Object(x,y,id)
    {
        this->basexp = 10;
        this->number_of_units = 0;
        this->max_number_of_units = 10;
    }
    ~Base()
    {

    }
    int getBaseXp();
    int getNumberOfUnits();
    int getMaxNumberOfUnits();
    int getMaxXp();
    void increaseNumberOfUnits(int amount);
    void decreaseNumberOfUnits(int amount);
    void createUnit(Field* f, bool& check);
    void decreaseXp(int amount);
    void increaseXp(int amount);
};


#endif //OOP_BASE_H

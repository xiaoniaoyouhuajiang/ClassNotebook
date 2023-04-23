#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <vector>
#include <string>
#include "Units/unit.h"
#include "compositeunit.h"
#include "UnitsFactory/archersfactory.h"
#include "UnitsFactory/cavalryfactory.h"
#include "UnitsFactory/infantryfactory.h"
#include "Units/unit.h"
#include "loggerproxy.h"

class FieldSnapshot;

class Base
{
public:
    Base(int, int, int, int, int);
    Unit* createUnit(std::string);
    void deleteUnit(Subject*);
    int getCapacityCount();
    int getCount();
    Unit* getCurrUnit();
    int getX();
    int getY();
    int getHealth();
    bool getDamage(int);

    friend class BaseStatusCommand;
    friend std::ostream& operator<< (std::ostream& out, const Base& base);
    friend class FieldSnapshot;

private:
    int baseNumb;
    int unitCount;
    const int maxCount;
    int unitCurr;
    int health;
    const int x, y;
    CompositeUnit* units;
    const std::vector <std::string> unitsNames = {"Flatbow", "Longbow", "Dragoon", "Hussar", "Swordsman", "Spearman"};
};

#endif // BASE_H

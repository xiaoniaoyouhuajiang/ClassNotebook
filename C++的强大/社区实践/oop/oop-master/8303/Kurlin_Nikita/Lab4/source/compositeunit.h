#ifndef COMPOSITEUNIT_H
#define COMPOSITEUNIT_H
#include "Units/unit.h"
#include "iostream"

class CompositeUnit : Unit
{
public:
    CompositeUnit();

    void addUnit(Unit*);
    bool deleteUnit(Subject*);
    void printAll();

    std::vector <Unit*> unitsMas;
};

#endif // COMPOSITEUNIT_H

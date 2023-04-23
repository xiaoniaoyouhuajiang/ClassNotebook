#ifndef OOP1_COMPOSITUNIT_H
#define OOP1_COMPOSITUNIT_H


#include "Unit.h"

class CompositUnit: public Unit{
public:
    std::vector<Unit*> masUnit;
    void addUnit(Unit* unit);
    bool removeUnit(Unit* unit);
    void printUnit();
};


#endif //OOP1_COMPOSITUNIT_H

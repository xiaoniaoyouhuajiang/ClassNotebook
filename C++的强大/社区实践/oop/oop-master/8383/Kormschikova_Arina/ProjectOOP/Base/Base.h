

#ifndef Base_h
#define Base_h

#include "Interfaces.h"
#include <vector>
#include <list>
#include "UnitsFactory.h"

class Unit;



class Base: public IBase{
public:
    int x, y;
    int hitPoint;
    int maxUnit;
    int unitsInBase;
    char type;
    MagicallyResilientFactory f1;
    PhysicallyResilientFactory f2;
    std::list <Unit*> units;
    
    Base();
    Base(int x, int y);
    bool createUnit() override;
    bool createUnit(char type) override;
    void showStat() override;
    void updateU() override;
    Unit* getUnit() override;
    void baseUpdate();
};

#endif /* Base_h */



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
    int unitsInBase;//Count of units defined to this base
    char type;
    std::vector <Unit*> units;
    LogProxy* loggerP;

    MagicallyResilientFactory f1;
    PhysicallyResilientFactory f2;
    
    Base();
    Base(int x, int y);
    bool createUnit() override;
    bool createUnit(char type) override;
    void showStat() override;
    void updateU() override;
    Unit* getUnit() override;
    void setLog(LogProxy* logger) override;
    void getDamage(int damage) override;
    void baseUpdate();
    friend std::ostream& operator <<(std::ostream& os, const Base& base);
};

#endif /* Base_h */

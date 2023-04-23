#pragma once
#include <list>
#include "field/cell.h"
#include "objects/object.h"
#include "fabrics/objectFabric.h"

#include "units/unit.h"
//#include "fabrics/health.h"
//#include "field/field.h"

//class Cell;
//class Unit;
//class Field;

class Base : virtual public Object, virtual public IPublisher     //component
{
public:
    Cell* baseCell;
    std::list<Unit*> units;
    const int maxCount;
    int curCount;

    Base();
    //Base(bool numbase);
    Base(int x, int y, bool numbase);
    virtual ~Base();

    Unit* createUnit(std::string str); 

    void attachObserver(IObserver *observer) override;
    void detachObserver(IObserver *observer) override;
    void notify(std::string message) override;
};

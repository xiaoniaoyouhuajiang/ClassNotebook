#ifndef COMPOSITE_H
#define COMPOSITE_H
#include "unit.h"
#include <list>
#include <vector>
class CompositeUnit : public Unit
{
public:
    CompositeUnit()=default;
    ~CompositeUnit()=default;
    void addUnit(Unit* unit);
    bool delUnit(Subject* unit);
    string getName();
    Unit *copyItem();
    string characteristic();
    Attributes *getAttributes() const;
    void move(int x, int y);
    Unit* getUnit(int)const;
    UnitsType getTypeEnum() const;
private:
    vector<Unit*> units;
};

#endif // COMPOSITE_H

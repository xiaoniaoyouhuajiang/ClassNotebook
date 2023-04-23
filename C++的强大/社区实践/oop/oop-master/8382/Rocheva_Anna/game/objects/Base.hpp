#ifndef LABOOP_BASE_HPP
#define LABOOP_BASE_HPP

#include <iostream>
#include "units/CompositeUnit.hpp"
#include "../FieldCell.hpp"

#include "Observer.hpp"

#define MAX_BASE_UNITS 10


class Base : public Observer{
public:
    Base();
    Coordinates * getCoordinates() final {return coordinates;};
    void setCoordinates(int x, int y) final;
    char getName() final {return 'B';};
    void createUnit(FieldCell *cell, UnitName name);
    void deleteUnit(FieldCell *cell, int flag=0);
    void moveUnit(FieldCell *cellIn, FieldCell *cellOut);
    void update(std::string newAction) override;
    Health *getHealth() { return health;};
    void printUnits() {units->printUnits();};
    void attackUnit(FieldCell *cell1, FieldCell *cell2);
private:
    Coordinates *coordinates;
    CompositeUnit *units;
    Health *health;
    int numUnits;
};


#endif //LABOOP_BASE_HPP

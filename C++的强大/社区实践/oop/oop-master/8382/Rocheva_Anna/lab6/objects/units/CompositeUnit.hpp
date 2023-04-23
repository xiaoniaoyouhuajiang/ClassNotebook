#ifndef LABOOP_COMPOSITEUNIT_HPP
#define LABOOP_COMPOSITEUNIT_HPP

#include "Unit.hpp"
#include <vector>

class CompositeUnit : public Unit{
public:
    char getName() final {return 'C';};
    void printUnits();
    void deleteUnit(Unit *unit);
    void addUnit(Unit *unit) {units.push_back(unit);};
    Unit& operator+=(NeutralObject &object) final {};
    std::vector <Unit*> getUnits() {return units;};
private:
    std::vector <Unit*> units;
};


#endif //LABOOP_COMPOSITEUNIT_HPP

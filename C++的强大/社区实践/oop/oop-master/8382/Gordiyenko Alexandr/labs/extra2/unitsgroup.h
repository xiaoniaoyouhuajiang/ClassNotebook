#ifndef LABS_UNITSGROUP_H
#define LABS_UNITSGROUP_H

#include <vector>
#include "../Units/Unit.h"

class UnitsGroup: public Unit {
public:
    std::vector<Unit*> unitsGroup;
    void addUnit(Unit* unit);
    void removeUnit(Unit* unit);
    void print();
    size_t size() { return unitsGroup.size(); }
    char type() { return 'G'; } // Group
};
#endif //LABS_UNITSGROUP_H

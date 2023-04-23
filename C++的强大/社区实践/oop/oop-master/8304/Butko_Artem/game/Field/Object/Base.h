#ifndef NEW_LR1_BASE_H
#define NEW_LR1_BASE_H

#include <vector>
#include <map>
#include "ObjectFabric.h"


class Base : public Object
{
private:
    int unitsOnBase_;
    int unitsInGame_;
    int limit_;
    ObjectFabric fabric_;
    std::map<char, int> UnitsOnBase_;
public:
    Base() = default;
    ~Base() = default;
    Base(int limit);
    void createUnit(char id);
    Object* createBase();
    Object* getUnit(char id, int quantity);
};

#endif //NEW_LR1_BASE_H

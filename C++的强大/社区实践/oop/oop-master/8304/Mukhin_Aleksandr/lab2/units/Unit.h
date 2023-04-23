#ifndef LAB2_UNIT_H
#define LAB2_UNIT_H

#include "Creator.h"
#include "HealthPoints.h"
#include "Attack.h"
#include <string>

class Unit {
public:
    int x = -1;
    int y = -1;
    Unit() = default;
    Unit(int def, int att, int intell) : defense(def), attack(att), intelligence(intell) {}

    HealthPoints defense;
    Attack attack;
    int intelligence;
    std::string unit_symbol{};

    virtual void greeting() const = 0;
    virtual ~Unit() {};
};


#endif

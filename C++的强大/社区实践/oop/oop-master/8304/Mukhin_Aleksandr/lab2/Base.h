#ifndef LAB2_BASE_H
#define LAB2_BASE_H
#include <memory>
#include <vector>
#include "HealthPoints.h"
#include "military/SpecialForces.h"
#include <iostream>
#include "Attack.h"

class Cell;
class Base {
    int max_size = 0;
    std::vector<std::shared_ptr<Unit>> units;
    friend class Boardfield;

public:
    int y = -1;
    int x = -1;
    Base() = default;
    Base(int);
    void add_unit(std::shared_ptr<Unit>&);
    void get_base();

    HealthPoints defense{100};
    Attack attack{50};
    int current_size = 0;
};


#endif

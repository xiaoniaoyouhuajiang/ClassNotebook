#ifndef LABOOP_LANDSCAPE_HPP
#define LABOOP_LANDSCAPE_HPP

#include "../objects/units/Unit.hpp"

enum Land {GRASS, MOUNTAINS, FOREST, SWAMP};

class Landscape{
protected:
    explicit Landscape() = default;
public:
    virtual char getName() = 0;
    virtual void changeAttribute(Unit *unit) = 0;
    virtual Land getLandName() = 0;
};


#endif //LABOOP_LANDSCAPE_HPP

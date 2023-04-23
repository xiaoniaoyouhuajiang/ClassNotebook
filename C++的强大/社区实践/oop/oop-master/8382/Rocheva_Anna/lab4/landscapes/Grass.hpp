#ifndef LABOOP_GRASS_HPP
#define LABOOP_GRASS_HPP


#include "Landscape.hpp"

class Grass : public Landscape{
public:
    Grass() : Landscape() {landName = GRASS;};
    char getName() final {return 'G';};
    void changeAttribute(Unit *unit) final {
        if (unit->getUnitName() == TANK)
            unit->changeAttributes(100, 0, 0);
        else
            unit->changeAttributes(0, -50, 0);
    };
    Land getLandName() final {return landName;};
private:
    Land landName;
};


#endif //LABOOP_GRASS_HPP

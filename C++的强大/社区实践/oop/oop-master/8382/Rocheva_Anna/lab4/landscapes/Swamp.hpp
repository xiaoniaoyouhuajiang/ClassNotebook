#ifndef LABOOP_SWAMP_HPP
#define LABOOP_SWAMP_HPP

#include "Landscape.hpp"

class Swamp : public Landscape{
public:
    Swamp() : Landscape() {landName = SWAMP;};
    char getName() final {return 'S';};
    void changeAttribute(Unit *unit) final {unit->changeAttributes(-50, 0, 0);};
    Land getLandName() final {return landName;};
private:
    Land landName;
};


#endif //LABOOP_SWAMP_HPP

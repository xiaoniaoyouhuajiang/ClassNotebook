#ifndef LABOOP_FOREST_HPP
#define LABOOP_FOREST_HPP

#include "Landscape.hpp"

class Forest : public Landscape{
public:
    Forest() : Landscape() {landName = FOREST;};
    char getName() final {return 'F';};
    void changeAttribute(Unit *unit) final {unit->changeAttributes(-10, 0, 0);};
    Land getLandName() final {return landName;};
private:
    Land landName;
};


#endif //LABOOP_FOREST_HPP

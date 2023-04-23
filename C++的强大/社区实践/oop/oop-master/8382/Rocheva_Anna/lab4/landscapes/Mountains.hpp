#ifndef LABOOP_MOUNTAINS_HPP
#define LABOOP_MOUNTAINS_HPP

#include "Landscape.hpp"

class Mountains : public Landscape{
public:
    Mountains() : Landscape() {landName = MOUNTAINS;};
    char getName() final {return 'M';};
    void changeAttribute(Unit *unit) final {unit->changeAttributes(100, 0, 0);};
    Land getLandName() final {return landName;};
private:
    Land landName;
};


#endif //LABOOP_MOUNTAINS_HPP

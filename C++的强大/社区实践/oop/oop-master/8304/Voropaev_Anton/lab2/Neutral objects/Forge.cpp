#include "Forge.h"

Forge::Forge(int x, int y){
    this->setPosition(x, y);
}

int Forge::operator()(Unit *unit) {
    strategy.change_attribute(unit, 5);
    return 0;
}

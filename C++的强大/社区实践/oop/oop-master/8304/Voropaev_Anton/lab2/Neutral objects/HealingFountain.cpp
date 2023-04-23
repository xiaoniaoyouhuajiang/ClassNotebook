#include "HealingFountain.h"

HealingFountain::HealingFountain(int x, int y){
    this->setPosition(x, y);
}

int HealingFountain::operator()(Unit* unit) {
    strategy.change_attribute(unit, unit->getHealth() / 3);
    return 0;
}

#include "Unit.h"


void Unit::interaction() const {
    mediator->make_action();
}

std::ostream& operator<<(std::ostream& out, const Unit& unit) {
    out << unit.get_health() << std::endl;
    out << unit.get_attack() << std::endl;
    out << unit.get_intelligence() << std::endl;
    return out;
}

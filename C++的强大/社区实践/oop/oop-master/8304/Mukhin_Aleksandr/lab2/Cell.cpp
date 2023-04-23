#include "Cell.h"

std::ostream& operator<<(std::ostream &os, Cell& cell) {
    if (cell.unit->x != -1) {
        os << "♘(" << cell.unit->defense.get_health() << ", " << cell.unit->attack.get_attack() << ", " << cell.unit->intelligence << ")";
    } else if (cell.base != nullptr && cell.base->x != -1) {
        os << "❆(" << cell.base->defense.get_health() << ", " << cell.base->attack.get_attack() << ", " << cell.base->current_size << ")";
    }
    if (cell.landscape != nullptr) {
        os << "♨";
    } else {
        os << "0(0, 0, 0)";
    }
    os << "       ";
    return os;
}


Cell& Cell::operator[](const std::shared_ptr<NeutralObject> object) {
    unit->defense.change(object->defense.get_health());
    unit->attack.change(object->attack.get_attack());
    unit->intelligence += object->intelligence;
    return *this;
}

Cell &Cell::operator[](Cell& second_object) {
    unit->defense.change(-second_object.unit->attack.get_attack());
    return *this;
}

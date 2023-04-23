#include "Cell.h"

std::ostream& operator<<(std::ostream &os, Cell& cell) {
    if (cell.is_unit()) {
        os << "♘(" << cell.unit->get_health() << ", " << cell.unit->get_attack() << ", " << cell.unit->get_intelligence() << ")";
    } else if (cell.is_base()) {
        os << "❆(" << cell.base->get_health() << ", " << cell.base->get_attack() << ", " << cell.base->current_size << ")";
    }
    if (cell.landscape != nullptr) {
        os << "♨";
    } else {
        os << "0(0, 0, 0)";
    }
    os << "       ";
    return os;
}

bool Cell::is_landscape() {
    return landscape != nullptr;
}

bool Cell::is_neutral_object() {
    return neutral_object != nullptr;
}

bool Cell::is_unit() {
    return unit != nullptr;
}

bool Cell::is_base() {
    return base != nullptr;
}

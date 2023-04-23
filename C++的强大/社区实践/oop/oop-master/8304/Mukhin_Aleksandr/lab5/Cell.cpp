#include "Cell.h"

bool Cell::is_landscape() const {
    return landscape != nullptr;
}

bool Cell::is_neutral_object() const {
    return neutral_object != nullptr;
}

bool Cell::is_unit() const {
    return unit != nullptr;
}

bool Cell::is_base() const {
    return base != nullptr;
}

std::ostream& operator<<(std::ostream& out, const Cell& cell) {
    if (cell.unit != nullptr) {
        out << *cell.unit;
        out << cell.unit->type << std::endl;
    } else {
        out << -1 << std::endl;
    }

    if (cell.landscape != nullptr) {
//        out << *cell.landscape;
        out << cell.landscape->type << std::endl;
    } else {
        out << -1 << std::endl;
    }

    if (cell.base != nullptr && cell.unit == nullptr) {
        out << *cell.base << std::endl;
    } else {
        out << -1 << std::endl;
    }

    if (cell.neutral_object != nullptr) {
//        out << *cell.neutral_object;
        out << cell.neutral_object->type << std::endl;
    } else {
        out << -1 << std::endl;
    }

    return out;
}

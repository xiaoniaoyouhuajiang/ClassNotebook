#include "Landscape.h"

int Landscape::get_health() const {
    return defense.get_health();
}

int Landscape::get_attack() const {
    return attack.get_attack();
}

int Landscape::get_intelligence() const {
    return intelligence;
}

#include "NeutralObject.h"

int NeutralObject::get_health() const {
    return defense.get_health();
}

int NeutralObject::get_attack() const {
    return attack.get_attack();
}

int NeutralObject::get_intelligence() const {
    return intelligence;
}

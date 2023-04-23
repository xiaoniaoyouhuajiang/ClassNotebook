#include "HealthPoints.h"

void HealthPoints::change(int value) {
    health += value;
}

int HealthPoints::get_health() const {
    return health;
}

HealthPoints::HealthPoints(int value) {
    health = value;
}



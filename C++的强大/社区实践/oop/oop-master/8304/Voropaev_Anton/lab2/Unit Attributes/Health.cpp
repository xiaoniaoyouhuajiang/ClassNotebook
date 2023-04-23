#include "Health.h"

Health::Health() {
    health = 0;
}

Health::Health(int h) {
    this->health = h;
}

int Health::getHealth() {
    return health;
}

void Health::setHealth(int h) {
    this->health = h;
}

void Health::actDamaged(int dmg) {
    this->health -= dmg;
}

void Health::actHealed(int heal) {
    this->health += heal;
}
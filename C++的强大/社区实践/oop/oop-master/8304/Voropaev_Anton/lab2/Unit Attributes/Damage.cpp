#include "Damage.h"


Damage::Damage() {
    damage = 0;
    range = 0;
}

Damage::Damage(int d, int r) {
    this->damage = d;
    this->range = r;
}

int Damage::getDamage() const {
    return damage;
}

void Damage::setDamage(int d) {
    damage = d;
}

int Damage::getRange() const {
    return range;
}

void Damage::setRange(int r) {
    range = r;
}

void Damage::DecreaseDmg(int debuff) {
    damage -= debuff;
}

void Damage::IncreaseDmg(int buff) {
    damage += buff;
}

void Damage::IncreaseRange(int buff) {
    this->range += buff;

}

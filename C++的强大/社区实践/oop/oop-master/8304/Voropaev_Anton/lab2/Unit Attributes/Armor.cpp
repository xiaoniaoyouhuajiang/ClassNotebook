#include "Armor.h"

Armor::Armor() {
    armor = 0;
}

Armor::Armor(int a) {
    this->armor = a;
}

int Armor::getArmor() const {
    return armor;
}

void Armor::setArmor(int a) {
    armor = a;
}

void Armor::DecreaseArmor(int debuff) {
    armor -= debuff;
}

void Armor::IncreaseArmor(int buff) {
    armor += buff;
}
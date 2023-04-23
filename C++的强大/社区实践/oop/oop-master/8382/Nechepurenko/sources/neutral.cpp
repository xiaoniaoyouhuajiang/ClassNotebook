#include "../headers/neutral.hpp"
#include <iostream>

void HealBuff::buff(Unit* u) {
    u->attributes.health += this->amount;
}
void DamageBuff::buff(Unit* u) {
    u->attributes.damage += this->amount;
}
void ArmorBuff::buff(Unit* u) {
    u->attributes.armor += this->amount;
}
void SpeedBuff::buff(Unit* u) {
    //std::cout << "Speed is not implemented yet" << std::endl;
}

Unit& operator+(Unit& u, HealBuff& buff) {
    buff.buff(&u);
    return u;
}

Unit& operator*(Unit& u, DamageBuff& buff) {
    buff.buff(&u);
    return u;
}

Unit& operator-(Unit& u, SpeedBuff& buff) {
    buff.buff(&u);
    return u;
}

Unit& operator/(Unit& u, ArmorBuff& buff) {
    buff.buff(&u);
    return u;
}

#include "Attack.h"

Attack::Attack(int value) {
    attack = value;
}

void Attack::change(int value) {
    attack += value;
}

int Attack::get_attack() const {
    return attack;
}

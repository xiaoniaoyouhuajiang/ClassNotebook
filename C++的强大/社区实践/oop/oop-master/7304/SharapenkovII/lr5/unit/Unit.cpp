//
// Created by smokfyz on 10.04.19.
//

#include <iostream>
#include "Unit.h"

Unit::Unit() {
    position = shared_ptr<Cell>(nullptr);
}

string Unit::getTypeName() const { return type_name; }

unsigned Unit::getAttack() const { return attack; }
unsigned Unit::getRange() const { return range; }
unsigned Unit::getHealth() const { return health; }
unsigned Unit::getHealthMax() const { return health_max; }
unsigned Unit::getEnergy() const { return energy; }
unsigned Unit::getEnergyMax() const { return energy_max; }
unsigned Unit::getStyle() const { return style; }

void Unit::setEnergy(unsigned i) { energy = i; }

void Unit::damage(unsigned d) {
    if(health <= d)
        destruction();

    health -= d;
}
void Unit::heal(unsigned h) { health = ( health + h > health_max ) ? health_max : health + h; }

void Unit::setPosition(shared_ptr<Cell> c) { position.swap(c); }

shared_ptr<Cell> Unit::getPosition() { return position; }

void Unit::attackUnit(shared_ptr<Unit> u) {
    if(attack <= energy) {
        u->damage(attack);
        energy -= attack;
    }
}

void Unit::reset() {
    health = health_max;
    energy = energy_max;
}

void Archer::destruction() {
    position->deleteUnit();
}

void Tank::destruction() {
    position->deleteUnit();
}

void Knight::destruction() {
    position->deleteUnit();
}

void King::destruction() {
    position->deleteUnit();
}

void Priest::destruction() {
    position->deleteUnit();
}

void Killer::destruction() {
    position->deleteUnit();
}

void OwnUnit::destruction() {
    position->deleteUnit();
}


//
// Created by anton on 5/9/20.
//

#include "Vitality.h"

#include "GameObject.h"

Vitality::Vitality(int health, int armour, float dmgMul, GameObject *master) : health(health), armour(armour),
                                                                               dmgMul(dmgMul), master(master) {}

void Vitality::damage(int amount) {
    health-=amount;
    if(health<=0)
        master->setToBeRemoved(true);
}

void Vitality::heal(int amount) {
    health+=amount;
    if(health>0 && master->isToBeRemoved())master->setToBeRemoved(false);
}

int Vitality::getHealth() const {
    return health;
}

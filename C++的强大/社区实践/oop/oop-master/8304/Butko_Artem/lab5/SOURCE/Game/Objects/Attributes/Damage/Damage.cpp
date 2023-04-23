//
// Created by Artem Butko on 08/05/2020.
//

#include "Damage.h"

void Damage::set(int damage, int range, int cost)
{
    this->damage_ = damage;
    this->damageRange_ = range;
    this->damageCost_ = cost;
}

int Damage::getDamage()
{
    return this->damage_;
}


int Damage::getRange()
{
    return this->damageRange_;
}

int Damage::getCost() {
    return this->damageCost_;
}


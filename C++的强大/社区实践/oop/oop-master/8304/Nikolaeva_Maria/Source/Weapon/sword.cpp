#include "sword.h"


Sword::Sword()
{
    damage = SWORD_DAMAGE;
    distance = SWORD_ATTACK_DISTANCE;
}


size_t Sword::getDamage() const
{
    return this->damage;
}


size_t Sword::getDistance() const
{
    return this->distance;
}


Weapon* Sword::clone()
{
    Sword* sword = new Sword;
    sword->distance = this->distance;
    sword->damage = this->damage;

    return sword;
}

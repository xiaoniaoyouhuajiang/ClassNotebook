#include "claws.h"


Claws::Claws()
{
    damage = CLAWS_DAMAGE;
    distance = CLAWS_ATTACK_DISTANCE;
}


size_t Claws::getDamage() const
{
    return this->damage;
}


size_t Claws::getDistance() const
{
    return this->distance;
}


Weapon* Claws::clone()
{
    Claws* claws = new Claws;
    claws->distance = this->distance;
    claws->damage = this->damage;

    return claws;
}

#include "bow.h"


Bow::Bow()
{
    damage = BOW_DAMAGE;
    distance = BOW_ATTACK_DISTANCE;
}


size_t Bow::getDamage() const
{
    return this->damage;
}


size_t Bow::getDistance() const
{
    return this->distance;
}


Weapon* Bow::clone()
{
    Bow* bow = new Bow;
    bow->distance = this->distance;
    bow->damage = this->damage;

    return bow;
}

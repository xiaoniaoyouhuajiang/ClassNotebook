#include "noweapon.h"


NoWeapon::NoWeapon()
{
    damage = NO_DAMAGE;
    distance = NO_ATTACK_DISTANCE;
}


size_t NoWeapon::getDamage() const
{
    return this->damage;
}


size_t NoWeapon::getDistance() const
{
    return this->distance;
}


Weapon* NoWeapon::clone()
{
    NoWeapon* noWeapon = new NoWeapon;
    noWeapon->distance = this->distance;
    noWeapon->damage = this->damage;

    return noWeapon;
}

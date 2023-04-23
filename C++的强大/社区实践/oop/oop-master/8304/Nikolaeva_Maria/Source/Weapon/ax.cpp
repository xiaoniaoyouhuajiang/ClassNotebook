#include "ax.h"


Ax::Ax()
{
    damage = AX_DAMAGE;
    distance = AX_ATTACK_DISTANCE;
}


size_t Ax::getDamage() const
{
    return this->damage;
}


size_t Ax::getDistance() const
{
    return this->distance;
}


Weapon* Ax::clone()
{
    Ax* ax = new Ax;
    ax->distance = this->distance;
    ax->damage = this->damage;

    return ax;
}

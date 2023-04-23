#include "bow.h"


Bow::Bow()
{
    distance = MELEE_DISTANCE;
    damage = SWORD_DMG;
}


Bow::Bow(const Bow& weapon)
{
    this->doCopy(weapon);
}


Bow& Bow::operator=(const Bow& weapon)
{
    if (this == &weapon) {
        return *this;
    }

    this->doCopy(weapon);

    return *this;
}


size_t Bow::getDamage() const
{
    return damage;
}


size_t Bow::getDistanceAttack() const
{
    return  distance;
}


std::shared_ptr<Weapon> Bow::clone() const
{
    return std::make_shared<Bow>(*this);
}

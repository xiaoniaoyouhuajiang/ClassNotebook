#include "magic.h"


Magic::Magic()
{
    distance = RANGE_DISTANCE;
    damage = MAGIC_DMG;
}


Magic::Magic(const Magic& weapon)
{
    this->doCopy(weapon);
}


Magic& Magic::operator=(const Magic& weapon)
{
    if (this == &weapon) {
        return *this;
    }

    this->doCopy(weapon);

    return *this;
}


size_t Magic::getDamage() const
{
    return damage;
}


std::shared_ptr<Weapon> Magic::clone() const
{
    return std::make_shared<Magic>(*this);
}


size_t Magic::getDistanceAttack() const
{
    return distance;
}

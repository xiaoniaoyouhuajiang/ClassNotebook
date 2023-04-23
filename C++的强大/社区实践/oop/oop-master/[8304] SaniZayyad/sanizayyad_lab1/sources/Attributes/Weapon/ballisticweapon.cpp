#include "ballisticweapon.hpp"

BallisticWeapon::BallisticWeapon()
{
    weaponType = "Ballistic";
    radius = BALLISTIC_RADIUS;
    distance = LONG_RANGE_DISTANCE;
    damage = BALLISTIC_DAMAGE;
}


BallisticWeapon::BallisticWeapon(const BallisticWeapon& weapon)
{
    this->doCopy(weapon);
}


BallisticWeapon& BallisticWeapon::operator=(const BallisticWeapon& weapon)
{
    if (this == &weapon) {
        return *this;
    }

    this->doCopy(weapon);

    return *this;
}


size_t BallisticWeapon::getDamage() const
{
    return damage;
}


std::unique_ptr<Weapon> BallisticWeapon::clone()
{
    std::unique_ptr<Weapon> weapon(new BallisticWeapon(*this));
    return weapon;
}


size_t BallisticWeapon::getRadiusAttack() const
{
    return radius;
}


size_t BallisticWeapon::getDistanceAttack() const
{
    return  distance;
}

std::string BallisticWeapon::getWeaponttype() const
{
    return weaponType;
}

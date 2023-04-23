#include "spearweapon.hpp"

SpearWeapon::SpearWeapon()
{
    weaponType = "Spear";
    radius = SWORD_SPEAR_RADIUS;
    distance = SHORT_RANGE_DISTANCE;
    damage = SWORD_SPEAR_DAMAGE;
}


SpearWeapon::SpearWeapon(const SpearWeapon& weapon)
{
    this->doCopy(weapon);
}


SpearWeapon& SpearWeapon::operator=(const SpearWeapon& weapon)
{
    if (this == &weapon) {
        return *this;
    }

    this->doCopy(weapon);

    return *this;
}


size_t SpearWeapon::getDamage() const
{
    return damage;
}


std::unique_ptr<Weapon> SpearWeapon::clone()
{
    std::unique_ptr<Weapon> weapon(new SpearWeapon(*this));
    return weapon;
}


size_t SpearWeapon::getRadiusAttack() const
{
    return radius;
}


size_t SpearWeapon::getDistanceAttack() const
{
    return  distance;
}

std::string SpearWeapon::getWeaponttype() const
{
    return weaponType;
}

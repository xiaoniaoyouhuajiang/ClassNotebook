#include "spearweapon.hpp"

SpearWeapon::SpearWeapon()
{
    weaponType = "Spear";
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


std::shared_ptr<Weapon> SpearWeapon::clone() const
{
    return std::make_shared<SpearWeapon>(*this);
}


size_t SpearWeapon::getDistanceAttack() const
{
    return  distance;
}

std::string SpearWeapon::getWeaponttype() const
{
    return weaponType;
}

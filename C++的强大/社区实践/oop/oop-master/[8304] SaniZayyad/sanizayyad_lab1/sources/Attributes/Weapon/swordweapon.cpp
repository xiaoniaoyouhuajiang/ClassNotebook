#include "swordweapon.hpp"

SwordWeapon::SwordWeapon()
{
    weaponType = "Sword";
    radius = SWORD_SPEAR_RADIUS;
    distance = SHORT_RANGE_DISTANCE;
    damage = SWORD_SPEAR_DAMAGE;
}


SwordWeapon::SwordWeapon(const SwordWeapon& weapon)
{
    this->doCopy(weapon);
}


SwordWeapon& SwordWeapon::operator=(const SwordWeapon& weapon)
{
    if (this == &weapon) {
        return *this;
    }

    this->doCopy(weapon);

    return *this;
}


size_t SwordWeapon::getDamage() const
{
    return damage;
}


std::unique_ptr<Weapon> SwordWeapon::clone()
{
    std::unique_ptr<Weapon> weapon(new SwordWeapon(*this));
    return weapon;
}


size_t SwordWeapon::getRadiusAttack() const
{
    return radius;
}


size_t SwordWeapon::getDistanceAttack() const
{
    return  distance;
}

std::string SwordWeapon::getWeaponttype() const
{
    return weaponType;
}

#include "swordweapon.hpp"

SwordWeapon::SwordWeapon()
{
    weaponType = "Sword";
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


std::shared_ptr<Weapon> SwordWeapon::clone() const
{
    return std::make_shared<SwordWeapon>(*this);
}



size_t SwordWeapon::getDistanceAttack() const
{
    return  distance;
}

std::string SwordWeapon::getWeaponttype() const
{
    return weaponType;
}

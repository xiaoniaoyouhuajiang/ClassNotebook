#include "ballisticweapon.hpp"

BallisticWeapon::BallisticWeapon()
{
    weaponType = "Ballistic";
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


std::shared_ptr<Weapon> BallisticWeapon::clone() const
{
    return std::make_shared<BallisticWeapon>(*this);

}

size_t BallisticWeapon::getDistanceAttack() const
{
    return  distance;
}

std::string BallisticWeapon::getWeaponttype() const
{
    return weaponType;
}

#include "arrowweapon.hpp"

ArrowWeapon::ArrowWeapon()
{
    weaponType = "Arrow";
    distance = SHORT_RANGE_DISTANCE;
    damage = ARROW_DAMAGE;
}


ArrowWeapon::ArrowWeapon(const ArrowWeapon& weapon)
{
    this->doCopy(weapon);
}


ArrowWeapon& ArrowWeapon::operator=(const ArrowWeapon& weapon)
{
    if (this == &weapon) {
        return *this;
    }

    this->doCopy(weapon);

    return *this;
}


size_t ArrowWeapon::getDamage() const
{
    return damage;
}


std::shared_ptr<Weapon> ArrowWeapon::clone() const
{
     return std::make_shared<ArrowWeapon>(*this);
}


size_t ArrowWeapon::getDistanceAttack() const
{
    return  distance;
}

std::string ArrowWeapon::getWeaponttype() const
{
    return weaponType;
}

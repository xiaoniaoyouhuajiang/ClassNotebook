#include "arrowweapon.hpp"

ArrowWeapon::ArrowWeapon()
{
    weaponType = "Arrow";
    radius = ARROW_RADIUS;
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


std::unique_ptr<Weapon> ArrowWeapon::clone()
{
    std::unique_ptr<Weapon> weapon(new ArrowWeapon(*this));
    return weapon;
}


size_t ArrowWeapon::getRadiusAttack() const
{
    return radius;
}


size_t ArrowWeapon::getDistanceAttack() const
{
    return  distance;
}

std::string ArrowWeapon::getWeaponttype() const
{
    return weaponType;
}

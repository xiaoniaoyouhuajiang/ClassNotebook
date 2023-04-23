#include "dragonfireweapon.hpp"

DragonFireWeapon::DragonFireWeapon()
{
    weaponType = "Dragon Fire";
    radius = DRAGON_FIRE_RADIUS;
    distance = DYNAMIC_RANGE_DISTANCE;
    damage = DRAGON_FIRE_DAMAGE;
}


DragonFireWeapon::DragonFireWeapon(const DragonFireWeapon& weapon)
{
    this->doCopy(weapon);
}


DragonFireWeapon& DragonFireWeapon::operator=(const DragonFireWeapon& weapon)
{
    if (this == &weapon) {
        return *this;
    }

    this->doCopy(weapon);

    return *this;
}


size_t DragonFireWeapon::getDamage() const
{
    return damage;
}


std::unique_ptr<Weapon> DragonFireWeapon::clone()
{
    std::unique_ptr<Weapon> weapon(new DragonFireWeapon(*this));
    return weapon;
}


size_t DragonFireWeapon::getRadiusAttack() const
{
    return radius;
}


size_t DragonFireWeapon::getDistanceAttack() const
{
    return  distance;
}

std::string DragonFireWeapon::getWeaponttype() const
{
    return weaponType;
}

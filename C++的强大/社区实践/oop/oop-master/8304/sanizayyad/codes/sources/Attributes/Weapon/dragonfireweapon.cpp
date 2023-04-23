#include "dragonfireweapon.hpp"

DragonFireWeapon::DragonFireWeapon()
{
    weaponType = "Dragon Fire";
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


std::shared_ptr<Weapon> DragonFireWeapon::clone() const
{
    return std::make_shared<DragonFireWeapon>(*this);

}


size_t DragonFireWeapon::getDistanceAttack() const
{
    return  distance;
}

std::string DragonFireWeapon::getWeaponttype() const
{
    return weaponType;
}

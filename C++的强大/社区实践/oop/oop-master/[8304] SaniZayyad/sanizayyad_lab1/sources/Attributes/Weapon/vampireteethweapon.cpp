#include "vampireteethweapon.hpp"

VampireTeethWeapon::VampireTeethWeapon()
{
    weaponType = "Vampire teeth";
    radius = VAMPIRE_RADIUS;
    distance = DYNAMIC_RANGE_DISTANCE;
    damage = VAMPIRE_DAMAGE;
}


VampireTeethWeapon::VampireTeethWeapon(const VampireTeethWeapon& weapon)
{
    this->doCopy(weapon);
}


VampireTeethWeapon& VampireTeethWeapon::operator=(const VampireTeethWeapon& weapon)
{
    if (this == &weapon) {
        return *this;
    }

    this->doCopy(weapon);

    return *this;
}


size_t VampireTeethWeapon::getDamage() const
{
    return damage;
}


std::unique_ptr<Weapon> VampireTeethWeapon::clone()
{
    std::unique_ptr<Weapon> weapon(new VampireTeethWeapon(*this));
    return weapon;
}


size_t VampireTeethWeapon::getRadiusAttack() const
{
    return radius;
}


size_t VampireTeethWeapon::getDistanceAttack() const
{
    return  distance;
}

std::string VampireTeethWeapon::getWeaponttype() const
{
    return weaponType;
}

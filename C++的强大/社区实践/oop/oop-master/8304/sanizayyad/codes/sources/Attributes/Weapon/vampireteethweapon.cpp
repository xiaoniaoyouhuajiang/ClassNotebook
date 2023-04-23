#include "vampireteethweapon.hpp"

VampireTeethWeapon::VampireTeethWeapon()
{
    weaponType = "Vampire teeth";
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


std::shared_ptr<Weapon> VampireTeethWeapon::clone() const
{
    return std::make_shared<VampireTeethWeapon>(*this);

}


size_t VampireTeethWeapon::getDistanceAttack() const
{
    return  distance;
}

std::string VampireTeethWeapon::getWeaponttype() const
{
    return weaponType;
}

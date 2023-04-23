#include "vampireteethweaponfactory.hpp"

std::shared_ptr<Weapon> VampireTeethWeaponFactory::createWeapon() const
{
    return std::make_shared<VampireTeethWeapon>();

}

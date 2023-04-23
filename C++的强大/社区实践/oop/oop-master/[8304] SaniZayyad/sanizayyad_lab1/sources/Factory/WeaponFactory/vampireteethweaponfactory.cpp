#include "vampireteethweaponfactory.hpp"

std::unique_ptr<Weapon> VampireTeethWeaponFactory::createWeapon()
{
    std::unique_ptr<Weapon> weapon(new VampireTeethWeapon);
    
    return weapon;
}

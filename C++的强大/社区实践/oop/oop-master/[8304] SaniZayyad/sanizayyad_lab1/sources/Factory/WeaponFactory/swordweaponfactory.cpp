#include "swordweaponfactory.hpp"

std::unique_ptr<Weapon> SwordWeaponFactory::createWeapon()
{
    std::unique_ptr<Weapon> weapon(new SwordWeapon);
    
    return weapon;
}

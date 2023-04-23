#include "arrowweaponfactory.hpp"

std::unique_ptr<Weapon> ArrowWeaponFactory::createWeapon()
{
    std::unique_ptr<Weapon> weapon(new ArrowWeapon);
    
    return weapon;
}

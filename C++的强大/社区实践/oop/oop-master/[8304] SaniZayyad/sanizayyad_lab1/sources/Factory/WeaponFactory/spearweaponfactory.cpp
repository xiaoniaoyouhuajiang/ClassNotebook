#include "spearweaponfactory.hpp"

std::unique_ptr<Weapon> SpearWeaponFactory::createWeapon()
{
    std::unique_ptr<Weapon> weapon(new SpearWeapon);
    
    return weapon;
}

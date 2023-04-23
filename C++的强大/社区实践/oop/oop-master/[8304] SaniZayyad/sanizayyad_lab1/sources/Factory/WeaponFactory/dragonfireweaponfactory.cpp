#include "dragonfireweaponfactory.hpp"

std::unique_ptr<Weapon> DragonFireWeaponFactory::createWeapon()
{
    std::unique_ptr<Weapon> weapon(new DragonFireWeapon);
    
    return weapon;
}

#include "ballisticweaponfactory.hpp"

std::unique_ptr<Weapon> BallisticWeaponFactory::createWeapon()
{
    std::unique_ptr<Weapon> weapon(new BallisticWeapon);
    
    return weapon;
}

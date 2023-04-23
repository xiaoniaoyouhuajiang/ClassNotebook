#include "arrowweaponfactory.hpp"

std::shared_ptr<Weapon> ArrowWeaponFactory::createWeapon() const
{
    return std::make_shared<ArrowWeapon>();
}

#include "dragonfireweaponfactory.hpp"

std::shared_ptr<Weapon> DragonFireWeaponFactory::createWeapon() const
{
    return std::make_shared<DragonFireWeapon>();

}

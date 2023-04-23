#include "ballisticweaponfactory.hpp"

std::shared_ptr<Weapon> BallisticWeaponFactory::createWeapon() const
{
       return std::make_shared<BallisticWeapon>();

}

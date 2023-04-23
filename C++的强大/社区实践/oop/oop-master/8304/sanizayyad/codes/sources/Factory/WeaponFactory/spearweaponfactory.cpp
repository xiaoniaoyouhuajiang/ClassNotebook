#include "spearweaponfactory.hpp"

std::shared_ptr<Weapon> SpearWeaponFactory::createWeapon() const
{
      return std::make_shared<SpearWeapon>();
}

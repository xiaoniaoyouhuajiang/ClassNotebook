#ifndef spearweaponfactory_hpp
#define spearweaponfactory_hpp

#include "weaponfactory.hpp"

#include <stdio.h>

class SpearWeaponFactory : public WeaponFactory
{
public:

    virtual std::shared_ptr<Weapon> createWeapon() const override;
};

#endif /* spearweaponfactory_hpp */

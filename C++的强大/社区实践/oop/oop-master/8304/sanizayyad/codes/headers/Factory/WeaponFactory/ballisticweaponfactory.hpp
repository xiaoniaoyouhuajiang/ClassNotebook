#ifndef ballisticweaponfactory_hpp
#define ballisticweaponfactory_hpp

#include "weaponfactory.hpp"

#include <stdio.h>

class BallisticWeaponFactory : public WeaponFactory
{
public:

    virtual std::shared_ptr<Weapon> createWeapon() const override;
};


#endif /* ballisticweaponfactory_hpp */

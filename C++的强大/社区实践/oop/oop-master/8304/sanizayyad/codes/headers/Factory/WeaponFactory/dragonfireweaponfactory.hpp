#ifndef dragonfireweaponfactory_hpp
#define dragonfireweaponfactory_hpp


#include "weaponfactory.hpp"

#include <stdio.h>

class DragonFireWeaponFactory : public WeaponFactory
{
public:

    virtual std::shared_ptr<Weapon> createWeapon() const override;
};


#endif /* dragonfireweaponfactory_hpp */

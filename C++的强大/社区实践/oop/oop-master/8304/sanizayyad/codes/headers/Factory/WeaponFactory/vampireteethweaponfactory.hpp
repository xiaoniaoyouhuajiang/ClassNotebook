#ifndef vampireteethweaponfactory_hpp
#define vampireteethweaponfactory_hpp

#include "weaponfactory.hpp"

#include <stdio.h>

class VampireTeethWeaponFactory : public WeaponFactory
{
public:

    virtual std::shared_ptr<Weapon> createWeapon() const override;
};


#endif /* VampireTeethweaponfactory_hpp */

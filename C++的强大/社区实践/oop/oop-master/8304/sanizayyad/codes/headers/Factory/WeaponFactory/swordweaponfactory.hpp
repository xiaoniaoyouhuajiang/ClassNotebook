#ifndef swordfactory_hpp
#define swordfactory_hpp

#include "weaponfactory.hpp"

#include <stdio.h>

class SwordWeaponFactory : public WeaponFactory
{
public:

    virtual std::shared_ptr<Weapon> createWeapon() const override;

};


#endif /* swordfactory_hpp */

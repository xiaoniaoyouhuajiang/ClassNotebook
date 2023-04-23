#ifndef arrowweaponfactory_hpp
#define arrowweaponfactory_hpp

#include "weaponfactory.hpp"

#include <stdio.h>

class ArrowWeaponFactory : public WeaponFactory
{
public:

    virtual std::shared_ptr<Weapon> createWeapon() const override;
};


#endif /* arrowweaponfactory_hpp */

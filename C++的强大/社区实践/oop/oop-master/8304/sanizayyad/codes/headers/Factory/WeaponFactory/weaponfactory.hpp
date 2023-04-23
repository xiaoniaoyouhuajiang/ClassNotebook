#ifndef weaponfactory_hpp
#define weaponfactory_hpp

#include "unit.hpp"
#include "swordweapon.hpp"
#include "spearweapon.hpp"
#include "arrowweapon.hpp"
#include "ballisticweapon.hpp"
#include "vampireteethweapon.hpp"
#include "dragonfireweapon.hpp"

#include <stdio.h>
#include <memory>

class WeaponFactory
{
public:
    virtual ~WeaponFactory() = default;
    
    virtual std::shared_ptr<Weapon> createWeapon() const = 0;
};


#endif /* weaponfactory_hpp */

#ifndef dragonfireweapon_hpp
#define dragonfireweapon_hpp

#include "weapon.hpp"

#include <stdio.h>

class DragonFireWeapon : public Weapon
{
public:
    explicit DragonFireWeapon();

    DragonFireWeapon(const DragonFireWeapon& weapon);
    DragonFireWeapon& operator=(const DragonFireWeapon& weapon);

    virtual size_t getDamage() const override;
    virtual size_t getDistanceAttack() const override;
    virtual std::string getWeaponttype() const override;

    virtual std::shared_ptr<Weapon> clone() const override;
};

#endif /* dragonfireweapon_hpp */

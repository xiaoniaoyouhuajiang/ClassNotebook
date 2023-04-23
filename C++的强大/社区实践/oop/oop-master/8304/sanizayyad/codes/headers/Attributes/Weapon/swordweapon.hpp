#ifndef swordweapon_hpp
#define swordweapon_hpp

#include "weapon.hpp"

#include <stdio.h>

class SwordWeapon : public Weapon
{
public:
    explicit SwordWeapon();

    SwordWeapon(const SwordWeapon& weapon);
    SwordWeapon& operator=(const SwordWeapon& weapon);

    virtual size_t getDamage() const override;
    virtual size_t getDistanceAttack() const override;
    virtual std::string getWeaponttype() const override;

    virtual std::shared_ptr<Weapon> clone() const override;
};


#endif /* swordweapon_hpp */

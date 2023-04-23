#ifndef spearweapon_hpp
#define spearweapon_hpp

#include "weapon.hpp"

#include <stdio.h>

class SpearWeapon : public Weapon
{
public:
    explicit SpearWeapon();

    SpearWeapon(const SpearWeapon& weapon);
    SpearWeapon& operator=(const SpearWeapon& weapon);

    virtual size_t getDamage() const override;
    virtual size_t getDistanceAttack() const override;
    virtual std::string getWeaponttype() const override;

    virtual std::shared_ptr<Weapon> clone() const override;
};

#endif /* spearweapon_hpp */

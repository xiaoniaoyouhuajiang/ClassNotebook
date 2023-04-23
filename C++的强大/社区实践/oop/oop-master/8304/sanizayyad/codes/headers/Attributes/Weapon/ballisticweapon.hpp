#ifndef ballisticweapon_hpp
#define ballisticweapon_hpp

#include "weapon.hpp"

#include <stdio.h>

class BallisticWeapon : public Weapon
{
public:
    explicit BallisticWeapon();

    BallisticWeapon(const BallisticWeapon& weapon);
    BallisticWeapon& operator=(const BallisticWeapon& weapon);

    virtual size_t getDamage() const override;
    virtual size_t getDistanceAttack() const override;
    virtual std::string getWeaponttype() const override;

    virtual std::shared_ptr<Weapon> clone() const override;
};

#endif /* ballisticweapon_hpp */

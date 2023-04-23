#ifndef vampireteethweapon_hpp
#define vampireteethweapon_hpp

#include "weapon.hpp"

#include <stdio.h>

class VampireTeethWeapon : public Weapon
{
public:
    explicit VampireTeethWeapon();

    VampireTeethWeapon(const VampireTeethWeapon& weapon);
    VampireTeethWeapon& operator=(const VampireTeethWeapon& weapon);

    virtual size_t getDamage() const override;
    virtual size_t getDistanceAttack() const override;
    virtual std::string getWeaponttype() const override;

    virtual std::shared_ptr<Weapon> clone() const override;
};

#endif /* VampireTeethWeapon_hpp */

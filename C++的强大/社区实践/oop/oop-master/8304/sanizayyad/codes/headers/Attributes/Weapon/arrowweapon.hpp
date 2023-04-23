#ifndef arrowweapon_hpp
#define arrowweapon_hpp

#include "weapon.hpp"

#include <stdio.h>

class ArrowWeapon : public Weapon
{
public:
    explicit ArrowWeapon();

    ArrowWeapon(const ArrowWeapon& weapon);
    ArrowWeapon& operator=(const ArrowWeapon& weapon);

    virtual size_t getDamage() const override;
    virtual size_t getDistanceAttack() const override;
    virtual std::string getWeaponttype() const override;

    virtual std::shared_ptr<Weapon> clone() const  override;
};

#endif /* arrowweapon_hpp */

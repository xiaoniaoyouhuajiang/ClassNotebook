#ifndef NOWEAPON_H
#define NOWEAPON_H

#include "weapon.h"


class NoWeapon : public Weapon
{
public:
    explicit NoWeapon();
    virtual ~NoWeapon() = default;

    virtual size_t getDamage() const override;

    virtual size_t getDistance() const override;

    virtual Weapon* clone() override;

};

#endif // NOWEAPON_H

#ifndef SWORD_H
#define SWORD_H

#include "weapon.h"


class Sword: public Weapon
{
public:
    explicit Sword();
    virtual ~Sword() = default;

    virtual size_t getDamage() const override;

    virtual size_t getDistance() const override;

    virtual Weapon* clone() override;

};

#endif // SWORD_H

#ifndef FIREBALL_H
#define FIREBALL_H

#include "weapon.h"


class FireBall : public Weapon
{
public:
    explicit FireBall();
    virtual ~FireBall() = default;

    virtual size_t getDamage() const override;

    virtual size_t getDistance() const override;

    virtual Weapon* clone() override;

};

#endif // FIREBALL_H

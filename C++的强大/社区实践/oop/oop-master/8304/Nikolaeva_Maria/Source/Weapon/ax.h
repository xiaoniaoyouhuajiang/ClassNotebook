#ifndef AX_H
#define AX_H

#include "weapon.h"


class Ax : public Weapon
{
public:
    explicit Ax();
    virtual ~Ax() = default;

    virtual size_t getDamage() const override;

    virtual size_t getDistance() const override;

    virtual Weapon* clone() override;
};

#endif // AX_H

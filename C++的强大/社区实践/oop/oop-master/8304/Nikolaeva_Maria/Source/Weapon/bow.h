#ifndef BOW_H
#define BOW_H

#include "weapon.h"


class Bow : public Weapon
{
public:
    explicit Bow();
    virtual ~Bow() = default;

    virtual size_t getDamage() const override;

    virtual size_t getDistance() const override;

    virtual Weapon* clone() override;

};

#endif // BOW_H

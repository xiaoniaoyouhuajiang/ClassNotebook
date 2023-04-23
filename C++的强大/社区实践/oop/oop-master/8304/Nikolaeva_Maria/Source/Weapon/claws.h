#ifndef CLAWS_H
#define CLAWS_H

#include "weapon.h"


class Claws : public Weapon
{
public:
    explicit Claws();
    virtual ~Claws() = default;

    virtual size_t getDamage() const override;

    virtual size_t getDistance() const override;

    virtual Weapon* clone() override;

};

#endif // CLAWS_H

#ifndef NOARMOR_H
#define NOARMOR_H

#include "armor.h"


class NoArmor : public Armor
{
public:
    explicit NoArmor();
    virtual ~NoArmor() = default;

    virtual double getResistance() const override;

    virtual Armor* clone() override;
};

#endif // NOARMOR_H

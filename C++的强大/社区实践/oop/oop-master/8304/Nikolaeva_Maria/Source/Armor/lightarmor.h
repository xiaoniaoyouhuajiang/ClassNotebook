#ifndef LIGHTARMOR_H
#define LIGHTARMOR_H

#include "armor.h"


class LightArmor : public Armor
{
public:
    explicit LightArmor();
    virtual ~LightArmor() = default;

    virtual double getResistance() const override;

    virtual Armor* clone() override;
};

#endif // LIGHTARMOR_H

#ifndef LIGHTARMOR_H
#define LIGHTARMOR_H

#include "armor.h"


class LightArmor : public Armor
{
public:
    explicit LightArmor();

    LightArmor(const LightArmor& armor);
    LightArmor& operator=(const LightArmor& armor);

    virtual std::shared_ptr<Armor> clone() const override;

    virtual double getResistance() const override;
};

#endif // LIGHTARMOR_H

#ifndef HEAVYARMOR_H
#define HEAVYARMOR_H

#include "armor.h"


class HeavyArmor : public Armor
{
public:
    explicit HeavyArmor();
    virtual ~HeavyArmor() = default;

    virtual double getResistance() const override;

    virtual Armor* clone() override;
};

#endif // HEAVYARMOR_H

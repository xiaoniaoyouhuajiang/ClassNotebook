#ifndef HEAVYARMOR_H
#define HEAVYARMOR_H

#include "armor.h"


class HeavyArmor : public Armor
{
public:
    explicit HeavyArmor();

    HeavyArmor(const HeavyArmor& armor);
    HeavyArmor& operator=(const HeavyArmor& armor);

    virtual std::shared_ptr<Armor> clone() const override;

    virtual double getResistance() const override;
};

#endif // HEAVYARMOR_H

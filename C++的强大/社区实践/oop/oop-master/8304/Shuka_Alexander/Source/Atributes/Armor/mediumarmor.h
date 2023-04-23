#ifndef MEDIUMARMOR_H
#define MEDIUMARMOR_H

#include "armor.h"


class MediumArmor : public Armor
{
public:
    explicit MediumArmor();

    MediumArmor(const MediumArmor& armor);
    MediumArmor& operator=(const MediumArmor& armor);

    virtual std::shared_ptr<Armor> clone() const override;

    virtual double getResistance() const override;
};

#endif // MEDIUMARMOR_H

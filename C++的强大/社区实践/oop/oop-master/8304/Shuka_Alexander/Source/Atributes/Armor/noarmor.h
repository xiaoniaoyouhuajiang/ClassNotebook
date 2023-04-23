#ifndef NOARMOR_H
#define NOARMOR_H

#include "armor.h"


class NoArmor : public Armor
{
public:
    explicit NoArmor();

    NoArmor(const NoArmor& armor);
    NoArmor& operator=(const NoArmor& armor);

    virtual std::shared_ptr<Armor> clone() const override;

    virtual double getResistance() const override;
};

#endif // NOARMOR_H

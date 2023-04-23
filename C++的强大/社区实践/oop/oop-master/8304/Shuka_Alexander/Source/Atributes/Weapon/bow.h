#ifndef BOW_H
#define BOW_H

#include "weapon.h"


class Bow : public Weapon
{
public:
    explicit Bow();

    Bow(const Bow& weapon);
    Bow& operator=(const Bow& weapon);

    virtual size_t getDamage() const override;
    virtual size_t getDistanceAttack() const override;

    virtual std::shared_ptr<Weapon> clone() const override;
};

#endif // BOW_H

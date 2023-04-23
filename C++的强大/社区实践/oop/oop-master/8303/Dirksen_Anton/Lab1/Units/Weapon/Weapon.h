//
// Created by mensch on 4/4/20.
//

#ifndef OOP_LABS_WEAPON_H
#define OOP_LABS_WEAPON_H

enum class DamageType{
    MAGICAL,
    PHYSICAL
};

class Weapon {
protected:
    int damage;
    DamageType damageType;
public:
    Weapon() = default;
    virtual ~Weapon() = default;
};


#endif //OOP_LABS_WEAPON_H

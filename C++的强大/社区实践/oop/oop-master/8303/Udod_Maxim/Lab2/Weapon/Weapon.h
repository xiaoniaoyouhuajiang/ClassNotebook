//
// Created by shenk on 14.02.2020.
//

#ifndef UNTITLED13_WEAPON_H
#define UNTITLED13_WEAPON_H

enum class WeaponType{

    MAGIC,
    PHYSIC,
    FAR,
    FIREARMS

};

class Weapon {

protected:

    WeaponType type;
    int damage;

public:

    int getDamage() const { return damage; }
    WeaponType getType() const { return type; }

    bool operator==(const Weapon &other){

        return type == other.type && damage == other.damage;

    }

    Weapon& operator=(const Weapon& other){

        if (this == &other) return *this;
        type = other.type;
        damage = other.damage;
        return *this;

    }

};


#endif //UNTITLED13_WEAPON_H

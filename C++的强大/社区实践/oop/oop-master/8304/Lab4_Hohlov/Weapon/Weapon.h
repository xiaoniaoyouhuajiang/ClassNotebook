
#ifndef UNTITLED13_WEAPON_H
#define UNTITLED13_WEAPON_H

#include <ostream>

enum class WeaponType{

    MAGIC,
    PHYSIC,
    FAR,


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

    friend std::ostream &operator<<(std::ostream &stream, const Weapon &weapon){

        stream << "Weapon( " << "Damage: " << weapon.damage << " )";
        return stream;

    }

};


#endif //UNTITLED13_WEAPON_H

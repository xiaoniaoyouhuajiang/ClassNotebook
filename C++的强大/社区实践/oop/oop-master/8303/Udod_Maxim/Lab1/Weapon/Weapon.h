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

};


#endif //UNTITLED13_WEAPON_H

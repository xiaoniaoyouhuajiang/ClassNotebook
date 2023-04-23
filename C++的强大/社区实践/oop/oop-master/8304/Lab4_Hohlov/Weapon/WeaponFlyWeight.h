
#ifndef UNTITLED13_WEAPONFLYWEIGHT_H
#define UNTITLED13_WEAPONFLYWEIGHT_H


#include <vector>
#include "Weapon.h"

class WeaponFlyWeight {

private:

    static WeaponFlyWeight *self;
    std::vector<Weapon*> weapons;

public:

    template <typename T>
    static T* getFlyWeight(){

        if (!self) self = new WeaponFlyWeight();

        T needWeapon;
        for (auto *weapon: self->weapons){

            if (needWeapon == *weapon){
                return static_cast<T*>(weapon);
            }

        }

        T *weaponPtr = new T();
        self->weapons.push_back(weaponPtr);
        return weaponPtr;

    }

};
#endif //UNTITLED13_WEAPONFLYWEIGHT_H

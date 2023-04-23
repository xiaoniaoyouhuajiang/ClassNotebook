

#ifndef UNTITLED13_LANDSCAPE_H
#define UNTITLED13_LANDSCAPE_H


#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"
#include "../Objects/GameObject.h"

class Landscape {

public:

    virtual void print(std::ostream &stream, GameObject &object) const = 0;
    virtual void print(std::ostream &stream) const = 0;

    virtual int getDamageFactor(WeaponType type) = 0;
    virtual int getAbsorptionFactor(ArmorType type) = 0;

    friend std::ostream& operator<<(std::ostream &stream, const Landscape &landscape){
        landscape.print(stream);
        return stream;
    }

};


#endif //UNTITLED13_LANDSCAPE_H

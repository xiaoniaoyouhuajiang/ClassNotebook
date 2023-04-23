//
// Created by shenk on 14.02.2020.
//

#ifndef UNTITLED13_ARMOR_H
#define UNTITLED13_ARMOR_H

enum class ArmorType{

    HEAVY,
    MEDIUM,
    LIGHT,
    MAGIC

};

class Armor {

protected:

    ArmorType type;
    int damageAbsorption;

public:

    Armor(){}
    int getDamageAbsorption() const { return damageAbsorption; }
    ArmorType getType(){ return type; }

    bool operator==(Armor &other){

        return type == other.type && damageAbsorption == other.damageAbsorption;

    }

    Armor& operator=(const Armor& other){

        if (this == &other) return *this;
        type = other.type;
        damageAbsorption = other.damageAbsorption;
        return *this;

    }

};


#endif //UNTITLED13_ARMOR_H

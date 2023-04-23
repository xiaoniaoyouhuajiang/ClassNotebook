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

};


#endif //UNTITLED13_ARMOR_H

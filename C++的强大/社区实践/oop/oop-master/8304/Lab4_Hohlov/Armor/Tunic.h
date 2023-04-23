

#ifndef UNTITLED13_TUNIC_H
#define UNTITLED13_TUNIC_H

#include "Armor.h"

class Tunic: public Armor{

public:
    Tunic(){

        damageAbsorption = 1;
        type = ArmorType::MAGIC;

    }

};

#endif //UNTITLED13_TUNIC_H

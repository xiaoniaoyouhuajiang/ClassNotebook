//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_VOLDEMORT_H
#define UNTITLED13_VOLDEMORT_H

#include "Wizard.h"
#include "../../../Weapon/AvadaKedavra.h"

class Voldemort: public Wizard{

public:

    Voldemort(): Wizard(*WeaponFlyWeight::getFlyWeight<AvadaKedavra>(), 7){}

};

#endif //UNTITLED13_VOLDEMORT_H

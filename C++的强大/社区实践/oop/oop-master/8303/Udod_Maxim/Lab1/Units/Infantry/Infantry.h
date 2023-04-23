//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_INFANTRY_H
#define UNTITLED13_INFANTRY_H


#include "../Unit.h"
#include "../../Armor/ChainArmor.h"

class Infantry: public Unit {

public:

    Infantry() {

        armor = ChainArmor();

    }

};


#endif //UNTITLED13_INFANTRY_H

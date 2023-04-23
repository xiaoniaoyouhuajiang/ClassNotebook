//
//  BoxWithArmor.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "BoxWithArmor.hpp"


Unit* BoxWithArmor::operator +=  (Unit* unit) {

    if (unit->name[0] != '$' && unit->name[1] != '$' && unit->armor.getPoint() < 10){
        unit->armor.inc(1);
    }

    return unit;
}



char* BoxWithArmor::getName () {
    return "BA";
}

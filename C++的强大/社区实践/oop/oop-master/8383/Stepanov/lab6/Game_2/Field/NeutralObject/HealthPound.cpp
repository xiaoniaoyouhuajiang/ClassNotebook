//
//  HealthPound.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "HealthPound.hpp"

Unit* HealthPound::operator +=  (Unit* unit)  {

    if (unit->name[0] != '$' && unit->name[1] != '$' && unit->health.getPoint() < 10){
        unit->health.inc(1);
    }

    return unit;
}



char* HealthPound::getName () {
    return "HP";
}

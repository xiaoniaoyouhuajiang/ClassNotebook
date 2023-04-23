//
//  WorkbenchForWeapons.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "WorkbenchForWeapons.hpp"


Unit* WorkbenchForWeapons::operator +=  (Unit* unit) {

     if (unit->name[0] != '$' && unit->name[1] != '$' && unit->attack.getPoint() < 10){
         unit->attack.inc(1);
         unit->armor.inc(-2);
     }

     return unit;
 }

 
 
char* WorkbenchForWeapons::getName () {
     return "WW";
 }

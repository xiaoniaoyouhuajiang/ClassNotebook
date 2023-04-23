//
//  Runner.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Runner.hpp"

void Runner::hit (Field *field, int x, int y)  {
     std::cout << "I'm hit and you're losing your points" << std::endl;
     
     Unit *u = field->getUnit(x, y);
     
    if (!u) return;
    log->write(adapter.adaptUnitAttack(name, attack.getPoint() , u->getName(), u->armor.getPoint(), u->health.getPoint()));

    u->incArmor(-(attack.getPoint()));

     
 }
 
 void Runner::motion () {
     std::cout << "I'm going very fast" << std::endl;
 }
 
void Runner::setName (char unitNumberInName) {
     if (unitNumberInName % 2 == 0) {
         name.push_back(unitNumberInName);
         name.push_back('!');
     } else {
         name.push_back('!');
         name.push_back(unitNumberInName);
     }
 }

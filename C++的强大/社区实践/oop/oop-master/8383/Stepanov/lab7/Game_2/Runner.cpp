//
//  Runner.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 25.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Runner.hpp"

void Runner::hit (Field &field, int x, int y)  {
     std::cout << "I'm hit and you're losing your points" << std::endl;
     
     Unit *u = field.getUnit(x, y);
     
     if (!u) return;
     
     u->incHealth(-(attack.getPoint()));
     
 }
 
 void Runner::motion () {
     std::cout << "I'm going very fast" << std::endl;
 }
 
void Runner::setName (char unitNumberInName) {
     if (unitNumberInName % 2 == 0) {
         name[0] = unitNumberInName;
         name[1] = '!';
     } else {
         name[0] = '!';
         name[1] = unitNumberInName;
     }
     name[2] = '\0';
 }

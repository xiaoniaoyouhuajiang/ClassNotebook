//
//  Shooter.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Shooter.hpp"

void Shooter::hit (Field *field, int x, int y) {
      std::cout << "I'm shooting at you" << std::endl;
    
    if (this->x < x) {
        
        for (int i = x; i < field->getWidth(); i++) {
            Unit *u = field->getUnit(i, y);
            if (!u) continue;
            u->incArmor(-(attack.getPoint()));
            log->write(adapter.adaptUnitAttack(name, attack.getPoint() , u->getName(), u->armor.getPoint(), u->health.getPoint()));

        }
        
    } else if (this->x > x) {
        
        for (int i = x; i >= 0; i--) {
            Unit *u = field->getUnit(i, y);
            if (!u) continue;
            u->incArmor(-(attack.getPoint()));
            log->write(adapter.adaptUnitAttack(name, attack.getPoint() , u->getName(), u->armor.getPoint(), u->health.getPoint()));

        }
        
    } else if (this->y < y) {
       
        for (int i = y; i < field->getHeight(); i++) {
            Unit *u = field->getUnit(x, i);
            if (!u) continue;
            u->incArmor(-(attack.getPoint()));
            log->write(adapter.adaptUnitAttack(name, attack.getPoint() , u->getName(), u->armor.getPoint(), u->health.getPoint()));

        }
    } else if (this-> y > y) {
        
        for (int i = y; i >= 0; i--) {
            Unit *u = field->getUnit(x, i);
            if (!u) continue;
            log->write(adapter.adaptUnitAttack(name, attack.getPoint() , u->getName(), u->armor.getPoint(), u->health.getPoint()));
            u->incArmor(-(attack.getPoint()));

        }

    }
  }
  
  void Shooter::motion () {
      std::cout << "I'm going and wathching you" << std::endl;
  }

void Shooter::setName (char unitNumberInName) {
    if (unitNumberInName % 2 == 0) {
        name.push_back(unitNumberInName);
        name.push_back('>');
    } else {
        name.push_back('<');
        name.push_back(unitNumberInName);
    }
}

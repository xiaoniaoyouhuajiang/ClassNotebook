//
//  Smoker.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Smoker.hpp"

void Smoker::hit (Field *field, int x, int y) {
    std::cout << "I'm smoking" << std::endl;
    
    for (int i = 0; i < 3; i++){
        
        for (int j = 0; j < 3; j++){
            Unit *u = nullptr;
            u = field->getUnit(this->x-1+i, this->y-1+j);
            
            if (!u || (i == 1 && j == 1)) continue;
            log->write(adapter.adaptUnitAttack(name, attack.getPoint() , u->getName(), u->armor.getPoint(), u->health.getPoint()));
            u->incHealth(-(attack.getPoint()));
            
        }
    }
}

void Smoker::motion () {
    std::cout << "I'm going and smoking" << std::endl;
}

void Smoker::setName (char unitNumberInName) {
    if (unitNumberInName % 2 == 0) {
        name.push_back(unitNumberInName);
        name.push_back('$');
    } else {
        name.push_back('$');
        name.push_back(unitNumberInName);
    }
}

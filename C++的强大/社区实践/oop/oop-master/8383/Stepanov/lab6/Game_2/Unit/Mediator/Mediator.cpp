//
//  Mediator.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 04.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Mediator.hpp"

void Mediator::specialAbility(Unit *smoker, Unit *unit){
    
    unit->incHealth(-(smoker->attack.getPoint()));
}

//
//  StrongRunner.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "StrongRunner.hpp"

StrongRunner::StrongRunner (char unitNumberInName) {
 
    health.setPoint(8);
    armor.setPoint(8);
    attack.setPoint(7);

    setName(unitNumberInName);
}

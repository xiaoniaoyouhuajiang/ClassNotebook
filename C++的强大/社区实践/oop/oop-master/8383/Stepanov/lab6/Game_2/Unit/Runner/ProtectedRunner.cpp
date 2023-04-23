//
//  ProtectedRunner.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ProtectedRunner.hpp"

ProtectedRunner::ProtectedRunner (char unitNumberInName) {
    
    health.setPoint(8);
    armor.setPoint(13);
    attack.setPoint(5);

    setName(unitNumberInName);
}

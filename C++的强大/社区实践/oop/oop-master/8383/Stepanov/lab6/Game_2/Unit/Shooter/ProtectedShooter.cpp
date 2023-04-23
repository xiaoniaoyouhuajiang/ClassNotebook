//
//  ProtectedShooter.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ProtectedShooter.hpp"

ProtectedShooter::ProtectedShooter (char unitNumberInName) {
    
    health.setPoint(5);
    armor.setPoint(10);
    attack.setPoint(4);

    setName(unitNumberInName);
}

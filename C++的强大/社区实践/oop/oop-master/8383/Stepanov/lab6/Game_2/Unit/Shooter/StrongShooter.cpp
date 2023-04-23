//
//  StrongShooter.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "StrongShooter.hpp"

StrongShooter:: StrongShooter (char unitNumberInName) {

       health.setPoint(5);
       armor.setPoint(5);
       attack.setPoint(6);

       setName(unitNumberInName);
       
       
   }

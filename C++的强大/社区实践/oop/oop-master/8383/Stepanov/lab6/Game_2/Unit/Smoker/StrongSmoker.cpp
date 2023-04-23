//
//  StrongSmoker.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "StrongSmoker.hpp"


StrongSmoker:: StrongSmoker (char unitNumberInName) {
       
       health.setPoint(10);
       armor.setPoint(10);
       attack.setPoint(3);

       setName(unitNumberInName);
   }

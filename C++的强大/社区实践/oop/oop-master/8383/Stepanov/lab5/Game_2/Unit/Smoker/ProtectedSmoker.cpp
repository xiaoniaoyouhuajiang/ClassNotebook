//
//  ProtectedSmoker.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ProtectedSmoker.hpp"

ProtectedSmoker::ProtectedSmoker (char unitNumberInName) {
      
      health.setPoint(15);
      armor.setPoint(15);
      attack.setPoint(1);
      
      setName(unitNumberInName);
    
        
  }

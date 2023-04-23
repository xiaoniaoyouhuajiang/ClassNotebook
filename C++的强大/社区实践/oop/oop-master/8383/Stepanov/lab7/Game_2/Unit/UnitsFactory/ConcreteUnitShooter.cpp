//
//  ConcreteUnitShooter.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ConcreteUnitShooter.hpp"

 Unit * ConcreteUnitShooter::CreateUnit (char unitNumberInName, bool isProtected) {
       if (isProtected){
           return new ProtectedShooter(unitNumberInName);
       }
       
       return new StrongShooter( unitNumberInName);
   }

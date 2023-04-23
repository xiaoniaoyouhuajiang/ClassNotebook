//
//  ConcreteUnitRunner.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ConcreteUnitRunner.hpp"

Unit* ConcreteUnitRunner::CreateUnit (char unitNumberInName, bool isProtected) {
    
     if (isProtected){
           return new ProtectedRunner(unitNumberInName);
       }

       return new StrongRunner(unitNumberInName);
}

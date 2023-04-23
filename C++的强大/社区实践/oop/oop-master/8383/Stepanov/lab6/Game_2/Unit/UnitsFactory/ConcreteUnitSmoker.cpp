//
//  ConcreteUnitSmoker.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ConcreteUnitSmoker.hpp"


Unit* ConcreteUnitSmoker::CreateUnit (char unitNumberInName, bool isProtected) {
    if (isProtected){
        return new ProtectedSmoker(unitNumberInName);
    }

    return new StrongSmoker(unitNumberInName);
}

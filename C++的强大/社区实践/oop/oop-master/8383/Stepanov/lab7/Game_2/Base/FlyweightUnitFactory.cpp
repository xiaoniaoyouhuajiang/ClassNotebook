//
//  FlyweightUnitFactory.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "FlyweightUnitFactory.hpp"

UnitID * FlyweightUnitFactory::getUnitID (int uid) {
    
    for (int i = 0; i < unitsID.size(); i++){

        if (uid == unitsID[i]->getUnitID())
            return unitsID[i];
    }

    UnitID *a = new UnitID();
    a->setUnitID(uid);

    unitsID.push_back(a);

    return unitsID[unitsID.size()-1];
    
}

//
//  FlyweightUnitFactory.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef FlyweightUnitFactory_hpp
#define FlyweightUnitFactory_hpp

#include <vector>

#include "UnitID.hpp"


class FlyweightUnitFactory {
    
    std::vector<UnitID *> unitsID;

public:
    UnitID * getUnitID (int uid);

};

#endif /* FlyweightUnitFactory_hpp */

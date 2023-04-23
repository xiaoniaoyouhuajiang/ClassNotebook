//
//  ConcreteUnitSmoker.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ConcreteUnitSmoker_hpp
#define ConcreteUnitSmoker_hpp

#include "UnitsFactory.hpp"
#include "StrongSmoker.hpp"
#include "ProtectedSmoker.hpp"

class ConcreteUnitSmoker: public UnitsFactory {

public:
    
    Unit* CreateUnit (char unitNumberInName, bool isProtected) override;
};

#endif /* ConcreteUnitSmoker_hpp */

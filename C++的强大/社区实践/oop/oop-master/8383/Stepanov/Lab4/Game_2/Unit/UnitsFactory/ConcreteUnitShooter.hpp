//
//  ConcreteUnitShooter.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ConcreteUnitShooter_hpp
#define ConcreteUnitShooter_hpp

#include "UnitsFactory.hpp"
#include "ProtectedShooter.hpp"
#include "StrongShooter.hpp"

class ConcreteUnitShooter: public UnitsFactory {

public:
    
    Unit* CreateUnit (char unitNumberInName, bool isProtected) override;
};

#endif /* ConcreteUnitShooter_hpp */

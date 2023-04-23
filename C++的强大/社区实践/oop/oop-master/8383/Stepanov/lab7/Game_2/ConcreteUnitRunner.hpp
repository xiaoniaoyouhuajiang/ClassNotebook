//
//  ConcreteUnitRunner.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 25.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ConcreteUnitRunner_hpp
#define ConcreteUnitRunner_hpp

#include "UnitsFactory.hpp"
#include "Unit.hpp"
#include "Runner.hpp"
#include "ProtectedRunner.hpp"

class ConcreteUnitRunner: public UnitsFactory {

public:
    
    Unit * CreateUnit (char unitNumberInName, bool isProtected) override;
};

#endif /* ConcreteUnitRunner_hpp */

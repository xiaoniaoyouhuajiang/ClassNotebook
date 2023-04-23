//
//  ConcreteUnitRunner.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ConcreteUnitRunner_hpp
#define ConcreteUnitRunner_hpp

#include "UnitsFactory.hpp"
#include "ProtectedRunner.hpp"
#include "StrongRunner.hpp"

class ConcreteUnitRunner: public UnitsFactory {

public:
    
    Unit * CreateUnit (char unitNumberInName, bool isProtected) override;
};

#endif /* ConcreteUnitRunner_hpp */

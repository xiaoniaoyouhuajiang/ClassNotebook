//
//  ConcreteHealthPound.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ConcreteHealthPound_hpp
#define ConcreteHealthPound_hpp

#include "NeutralObjectFactory.hpp"
#include "HealthPound.hpp"

class ConcreteHealthPound: public NeutralObjectFactory {

public:
    
    NeutralObject* CreateNeutralObject () override;
    
};

#endif /* ConcreteHealthPound_hpp */

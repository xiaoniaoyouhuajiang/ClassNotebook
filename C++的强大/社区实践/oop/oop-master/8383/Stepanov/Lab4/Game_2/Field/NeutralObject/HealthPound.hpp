//
//  HealthPound.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef HealthPound_hpp
#define HealthPound_hpp

#include "Unit.hpp"
#include "NeutralObject.hpp"

class HealthPound: public NeutralObject {
    
    Unit* operator +=  (Unit* unit) override;
    char* getName () override;
    
};

#endif /* HealthPound_hpp */

//
//  ConcretePowerChemical.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ConcretePowerChemical_hpp
#define ConcretePowerChemical_hpp

#include "NeutralObjectFactory.hpp"
#include "PowerChemical.hpp"

class ConcretePowerChemical: public NeutralObjectFactory {

public:
    
    NeutralObject* CreateNeutralObject () override;
    
};

#endif /* ConcretePowerChemical_hpp */

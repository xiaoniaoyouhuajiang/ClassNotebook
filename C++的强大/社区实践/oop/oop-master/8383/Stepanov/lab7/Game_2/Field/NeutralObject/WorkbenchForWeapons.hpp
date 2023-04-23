//
//  WorkbenchForWeapons.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef WorkbenchForWeapons_hpp
#define WorkbenchForWeapons_hpp

#include "NeutralObject.hpp"
#include "Unit.hpp"

class WorkbenchForWeapons: public NeutralObject {
    
    Unit* operator +=  (Unit* unit) override;

    
    
    char* getName () override;
};

#endif /* WorkbenchForWeapons_hpp */

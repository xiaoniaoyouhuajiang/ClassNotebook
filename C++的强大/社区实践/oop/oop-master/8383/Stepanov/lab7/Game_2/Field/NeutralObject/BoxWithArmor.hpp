//
//  BoxWithArmor.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef BoxWithArmor_hpp
#define BoxWithArmor_hpp

#include "NeutralObject.hpp"
#include "Unit.hpp"

class BoxWithArmor: public NeutralObject {
    
    Unit* operator +=  (Unit* unit) override;

    char* getName () override;
};
#endif /* BoxWithArmor_hpp */

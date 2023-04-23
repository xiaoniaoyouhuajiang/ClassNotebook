//
//  PowerChemical.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef PowerChemical_hpp
#define PowerChemical_hpp

#include "NeutralObject.hpp"
#include "Unit.hpp"

class PowerChemical: public NeutralObject {
    
    Unit* operator +=  (Unit* unit) override;

    char* getName () override;
};

#endif /* PowerChemical_hpp */

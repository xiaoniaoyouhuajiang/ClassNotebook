//
//  Smoker.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Smoker_hpp
#define Smoker_hpp

#include <iostream>

#include "Field.hpp"
#include "Unit.hpp"

class Smoker: public Unit {
    
public:
    
    void hit (Field *field, int x, int y) override;
    
    void motion () override;
    
    void setName (char unitNumberInName) override;
};

#endif /* Smoker_hpp */

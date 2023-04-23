//
//  Runner.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 25.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Runner_hpp
#define Runner_hpp

#include <iostream>

#include "Unit.hpp"
#include "Field.hpp"

//class Field;

class Runner: public Unit {

public:
    
    void hit (Field &field, int x, int y) override;
    void motion () override;
    void setName (char unitNumberInName) override;
};

#endif /* Runner_hpp */

//
//  Runner.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Runner_hpp
#define Runner_hpp

#include "Field.hpp"
#include "Unit.hpp"

#include "ProxyLog.hpp"

class Runner: public Unit {

public:
    
    void hit (Field *field, int x, int y) override;
    void motion () override;
    void setName (char unitNumberInName) override;
};


#endif /* Runner_hpp */

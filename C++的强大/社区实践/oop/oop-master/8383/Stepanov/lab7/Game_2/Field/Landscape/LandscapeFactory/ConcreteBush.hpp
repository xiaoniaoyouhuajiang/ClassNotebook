//
//  ConcreteBush.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ConcreteBush_hpp
#define ConcreteBush_hpp

#include "LandscapeFactory.hpp"
#include "Bush.hpp"

class ConcreteBush: public LandscapeFactory {

public:
    
    Landscape * CreateLandscap () override;
};
#endif /* ConcreteBush_hpp */

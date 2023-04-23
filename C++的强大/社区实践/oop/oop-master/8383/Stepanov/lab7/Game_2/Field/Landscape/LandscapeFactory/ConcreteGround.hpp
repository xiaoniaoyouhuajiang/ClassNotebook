//
//  ConcreteGround.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ConcreteGround_hpp
#define ConcreteGround_hpp

#include "LandscapeFactory.hpp"
#include "Ground.hpp"

class ConcreteGround: public LandscapeFactory {

public:
    
    Landscape * CreateLandscap () override;
};
#endif /* ConcreteGround_hpp */

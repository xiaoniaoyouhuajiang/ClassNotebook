//
//  ConcreteDeepPuddel.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ConcreteDeepPuddel_hpp
#define ConcreteDeepPuddel_hpp

#include "LandscapeFactory.hpp"
#include "DeepPuddel.hpp"

class ConcreteDeepPuddel: public LandscapeFactory {

public:
    
    Landscape* CreateLandscap () override;
};

#endif /* ConcreteDeepPuddel_hpp */

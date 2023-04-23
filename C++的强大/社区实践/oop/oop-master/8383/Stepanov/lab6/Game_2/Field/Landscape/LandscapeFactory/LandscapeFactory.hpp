//
//  LandscapFactory.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef LandscapeFactory_hpp
#define LandscapeFactory_hpp

#include "Landscape.hpp"

class LandscapeFactory {

public:
    
    virtual Landscape * CreateLandscap () = 0;
};

#endif /* LandscapFactory_hpp */

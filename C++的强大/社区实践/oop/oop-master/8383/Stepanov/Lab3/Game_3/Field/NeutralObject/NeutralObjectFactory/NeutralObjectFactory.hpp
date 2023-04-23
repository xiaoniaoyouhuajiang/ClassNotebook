//
//  NeutralObjectFactory.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef NeutralObjectFactory_hpp
#define NeutralObjectFactory_hpp

#include "NeutralObject.hpp"

class NeutralObjectFactory {

public:
    
    virtual NeutralObject* CreateNeutralObject () = 0;
};
#endif /* NeutralObjectFactory_hpp */

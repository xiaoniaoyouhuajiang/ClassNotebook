//
//  ProxyLandscape.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ProxyLandscape_hpp
#define ProxyLandscape_hpp

#include "Landscape.hpp"
#include "Unit.hpp"

class Proxy: public Landscape {
    
    Landscape * landscape;
    char name;
    
public:
    Proxy (Landscape * u);
    bool doSomething (Unit* u);
    char getName () override;
};

#endif /* ProxyLandscape_hpp */

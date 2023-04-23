//
//  SpawnHandler.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef SpawnHandler_hpp
#define SpawnHandler_hpp

#include "AbstractHandler.hpp"

class SpawnHandler: public AbstractHandler {
    
    
public:
    
    bool Handle(std::string request) override;
    
    
    
};




#endif /* SpawnHandler_hpp */

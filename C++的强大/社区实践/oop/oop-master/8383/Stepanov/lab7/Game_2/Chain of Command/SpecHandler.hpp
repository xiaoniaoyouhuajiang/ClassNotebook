//
//  SpecHandler.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef SpecHandler_hpp
#define SpecHandler_hpp

#include "AbstractHandler.hpp"

class SpecHandler: public AbstractHandler {
    
    
public:
    
    bool Handle(std::string request) override;
    
};

#endif /* SpecHandler_hpp */

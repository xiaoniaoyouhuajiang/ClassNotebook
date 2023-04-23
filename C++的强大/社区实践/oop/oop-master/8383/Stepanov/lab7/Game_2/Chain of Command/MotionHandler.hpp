//
//  MotionHandler.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef MotionHandler_hpp
#define MotionHandler_hpp

#include "AbstractHandler.hpp"

class MotionHandler: public AbstractHandler {
    
    
public:
    
    bool Handle(std::string request) override;
    
};

#endif /* MotionHandler_hpp */

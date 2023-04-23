//
//  ExitHandler.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ExitHandler_hpp
#define ExitHandler_hpp

#include "AbstractHandler.hpp"

class ExitHandler: public AbstractHandler {
    
    
public:
    
    bool Handle(std::string request) override;
    
};

#endif /* ExitHandler_hpp */

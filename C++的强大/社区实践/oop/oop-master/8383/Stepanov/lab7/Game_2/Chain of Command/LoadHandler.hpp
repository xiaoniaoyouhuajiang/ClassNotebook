//
//  LoadHandler.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 03.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef LoadHandler_hpp
#define LoadHandler_hpp

#include "AbstractHandler.hpp"

class LoadHandler: public AbstractHandler {
    
    
public:
    
    bool Handle(std::string request) override;
    
};
#endif /* LoadHandler_hpp */

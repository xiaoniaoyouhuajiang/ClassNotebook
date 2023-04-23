//
//  SaveHandler.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 02.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef SaveHandler_hpp
#define SaveHandler_hpp

#include "AbstractHandler.hpp"

class SaveHandler: public AbstractHandler {
    
    
public:
    
    bool Handle(std::string request) override;
    
};

#endif /* SaveHandler_hpp */

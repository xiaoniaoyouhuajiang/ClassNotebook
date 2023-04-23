//
//  LoadHandler.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 03.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "LoadHandler.hpp"

bool LoadHandler::Handle(std::string request) {
    
    if (request == "load") {
        return true;
    } else if (next_handler_){
        return next_handler_->Handle(request);
    } else {
        return false;
    }
    
}

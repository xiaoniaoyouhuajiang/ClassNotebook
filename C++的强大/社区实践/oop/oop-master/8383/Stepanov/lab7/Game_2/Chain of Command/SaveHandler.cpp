//
//  SaveHandler.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 02.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "SaveHandler.hpp"

bool SaveHandler::Handle(std::string request) {
    
    if (request == "save") {
        return true;
    } else if (next_handler_){
        return next_handler_->Handle(request);
    } else {
        return false;
    }
    
}

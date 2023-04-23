//
//  SpecHandler.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "SpecHandler.hpp"

bool SpecHandler::Handle(std::string request) {
    
    if (request == "spec") {
        return true;
    } else if (next_handler_){
        return next_handler_->Handle(request);
    } else {
        return false;
    }
    
}

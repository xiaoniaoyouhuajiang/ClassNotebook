//
//  ExitHandler.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ExitHandler.hpp"

bool ExitHandler::Handle(std::string request) {
    
    if (request == "exit") {
        return true;
    } else if (next_handler_){
        return next_handler_->Handle(request);
    } else {
        return false;
    }
    
}

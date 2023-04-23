//
//  MotionHandler.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "MotionHandler.hpp"

bool MotionHandler::Handle(std::string request) {
    
    if ((request[1] == 'm' || request[1] == 'h') &&
        (request[0] == 'w' || request[0] == 'a' || request[0] == 's' || request[0] == 'd') ) {
        return true;
    } else if (next_handler_){
        return next_handler_->Handle(request);
    } else {
        return false;
    }
    
}

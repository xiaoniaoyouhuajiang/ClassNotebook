//
//  AbstractHandler.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "AbstractHandler.hpp"

AbstractHandler::AbstractHandler() : next_handler_(nullptr) {
}

Handler * AbstractHandler::SetNext(Handler *handler) {
       this->next_handler_ = handler;
       return handler;
   }

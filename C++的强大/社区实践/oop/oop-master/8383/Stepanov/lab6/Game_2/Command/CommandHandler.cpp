//
//  CommandHandler.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "CommandHandler.hpp"

CommandHandler::CommandHandler(ProxyLog *log){
    
    moveCommand = new MoveCommand();
    hitCommand = new HitCommand();
    
    this->log = log;
    
}

bool CommandHandler::move (Unit* unit, Field *field, int toX, int toY){
   return  moveCommand->execute(log, unit, field, toX, toY);
    
    
    
}

bool CommandHandler::hit (Unit* unit, Field *field, int toX, int toY){
   return hitCommand->execute(log, unit, field, toX, toY);
    
}

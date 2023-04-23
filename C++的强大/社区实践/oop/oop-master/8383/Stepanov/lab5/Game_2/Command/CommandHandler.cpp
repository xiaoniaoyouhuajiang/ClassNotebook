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

void CommandHandler::move (Unit* unit, Field *field, int toX, int toY){
    moveCommand->execute(log, unit, field, toX, toY);
    
    
    
}

void CommandHandler::hit (Unit* unit, Field *field, int toX, int toY){
    hitCommand->execute(log, unit, field, toX, toY);
    
}

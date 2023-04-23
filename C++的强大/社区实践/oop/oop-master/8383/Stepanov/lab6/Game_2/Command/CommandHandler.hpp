//
//  CommandHandler.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef CommandHandler_hpp
#define CommandHandler_hpp

#include "Command.hpp"
#include "MoveCommand.hpp"
#include "HitCommand.hpp"
#include "Field.hpp"
#include "Unit.hpp"

#include "ProxyLog.hpp"

class CommandHandler {
    
private:
    
    Command *moveCommand;
    Command *hitCommand;
    
    ProxyLog *log;
    
    
public:
    
    CommandHandler(ProxyLog *log);
    
    bool move (Unit* unit, Field *field, int toX, int toY);
    bool hit (Unit* unit, Field *field, int toX, int toY);
    
};

#endif /* CommandHandler_hpp */

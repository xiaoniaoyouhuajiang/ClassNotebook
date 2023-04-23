//
//  MoveCommand.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef MoveCommand_hpp
#define MoveCommand_hpp

#include <string>

#include "Command.hpp"
#include "Unit.hpp"
#include "Field.hpp"
#include "ProxyLandscape.hpp"

#include "ProxyLog.hpp"
#include "Adapter.hpp"

class MoveCommand: public Command{
    
     Adapter adapter;
    
public:
    void execute(ProxyLog *log, Unit * unit, Field * field, int toX, int toY) override;
};

#endif /* MoveCommand_hpp */

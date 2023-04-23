
//
//  MoveCommand.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "MoveCommand.hpp"

bool MoveCommand::execute(ProxyLog *log, Unit * unit, Field * field, int toX, int toY) {
    
    log->write(adapter.adaptMove(unit->getName(), unit->getX(), unit->getY(), toX, toY));
    
   
         
      if (field->whatInCell(toX, toY) == 4){ // if whatInCell == 4 -> in Cell only landscape
              
          Proxy p (field->getLandscape(toX, toY));
          
          log->write(adapter.adaptLandscape(p.getName()));
              
          if (p.doSomething(unit) && field->replaceUnit(unit->getX(), unit->getY(), toX, toY)){
                  
              unit->setXY(toX, toY);
              log->write(adapter.isComplited(true));
              return true;
          }
              
          
         
    }
    
    log->write(adapter.isComplited(false));
    return false;
}

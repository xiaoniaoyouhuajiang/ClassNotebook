//
//  HitCommand.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "HitCommand.hpp"

void HitCommand::execute(ProxyLog *log, Unit * unit, Field * field, int toX, int toY) {
    
         if (unit->uid != 0 && field->whatInCell(toX, toY) == 2) {   // if uid == 0 -> chosenUnit is Smoker
                                                                           // whatInCell == 2 -> in cell neutralObject
             NeutralObject *n = field->getNeutralObject(toX, toY);
             
             if (n) {
                 log->write(adapter.adaptUnitWithObject(unit->getName(), unit->health.getPoint(), unit->armor.getPoint(), unit->attack.getPoint(), n->getName()));
                 *n += unit;
             }
             
             
         } else {
             log->write(adapter.adaptHit(unit->getName(), unit->getX(), unit->getY(), toX, toY));
             
             if (unit->attackIsBlocked){
                 std::cout << "Attack is blocked on this landscape" << std::endl;
                 log->write("Атака юнита заблокирована");
                 log->write(adapter.isComplited(false));
                 return;
             }
             unit->hit(field, toX, toY);
             log->write(adapter.isComplited(true));
         }

    
}

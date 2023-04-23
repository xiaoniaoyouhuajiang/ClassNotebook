#include "FieldCommand.h"
#include "Gamefield.h"
#include "MoveCommand.h"
#include "AttackCommand.h"
#include "BaseCommand.h"
#include "UnitInfoCommand.h"




FieldCommand::FieldCommand(GameField* field, int x, int y)
    :field(field), coordX(x), coordY(y)
{}



Event FieldCommand::execute(Event event){
    switch (event.type) {
       case Event::MOVE:{
         Unit* unit = (Unit*)field->getObj(coordX,coordY);
         MoveCommand move(unit, event.coord.x, event.coord.y);
         return move.execute(event);
       }
       case Event::ATTACK:{
         Unit* unit = (Unit*)field->getObj(coordX, coordY);
         AttackCommand attack(unit);
         return attack.execute(event);
       }
       case Event::BASE_INFO:
       case Event::UNIT_CREATE:{
         Base* base = (Base*)field->getObj(coordX, coordY);
         BaseCommand baseCommand(base);
         return baseCommand.execute(event);
       }
       case Event::UNIT_INFO:{
         Unit* unit = (Unit*)field->getObj(coordX, coordY);
         UnitInfoCommand command(unit);
         return command.execute(event);
       }

       default:{
         Event res; res.type = Event::ERROR;
         return res;
       }
    }


}




FieldCommand::~FieldCommand()
{

}

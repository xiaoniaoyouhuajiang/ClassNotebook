#include "MoveCommand.h"
#include "Unit.h"



MoveCommand::MoveCommand(Unit* unit, int destX, int destY)
  :unit(unit), destX(destX), destY(destY)
{}


Event MoveCommand::execute(Event event){
    Event result;
    if (event.type==Event::MOVE && unit){
        bool res = unit->move(destX, destY);
        if (res == false){
            result.type = Event::ERROR;
        }
        result.type = Event::MOVE;
    }
    else {
        result.type = Event::ERROR;
    }

    return result;
}



MoveCommand::~MoveCommand()
{

}

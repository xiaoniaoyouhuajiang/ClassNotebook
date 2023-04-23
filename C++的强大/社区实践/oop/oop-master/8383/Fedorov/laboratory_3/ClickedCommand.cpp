#include "ClickedCommand.h"
#include "GameObj.h"
#include "Gamefield.h"
#include "FieldCommand.h"
#include "CreateBaseCommand.h"


Event ClickedCommand::execute(Event event){
    Event ev;
    if (cellX<0||cellY<0||cellX>field->getHeight()-1||cellY>field->getWidth()-1){
        ev.type = Event::ERROR;
        return ev;
    }

    if (event.type==Event::CLICKED && field){
        FieldCommand command(field, cellX, cellY);
        Obj obj = field->getObj(cellX,cellY);
        if(obj){
         if (obj->isHero()){
            ev.type = Event::UNIT_INFO;
            return command.execute(ev);
          }
         else if (!obj->isNeutral()){
            ev.type = Event::BASE_INFO;
            return command.execute(ev);
         }
         else {
            ev.type = Event::ERROR;
            return ev;
        }
      }
    }
    else if (event.type==Event::UNIT_ACTION && field){
        FieldCommand command(field, event.coord.x, event.coord.y);
        Obj obj = field->getObj(cellX,cellY);

        if (obj==nullptr || obj->isNeutral()){
            ev.type = Event::MOVE;
            ev.coord.x = cellX; ev.coord.y = cellY;
            return command.execute(ev);
        }

        else if (!obj->isNeutral()){
            ev.type = Event::ATTACK;
            ev.attackCoord.x = cellX; ev.attackCoord.y = cellY;
            return command.execute(ev);
        }

        else {
            ev.type = Event::ERROR;
            return ev;
        }
    }


    ev.type = Event::ERROR;
    return ev;
}




ClickedCommand::ClickedCommand(GameField* field,int x,int y)
    :field(field), cellX(x), cellY(y) {}












ClickedCommand::~ClickedCommand()
{

}

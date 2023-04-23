#include "GameFacade.h"
#include "Game.h"
#include "ClickedCommand.h"
#include "CreateBaseCommand.h"


bool GameFacade::createBase(int x, int y){
   CreateBaseCommand command(baseConstructor);
   Event event;
   event.type = Event::HBASE_CREATE;
   event.base.x = x; event.base.y = y;
   Event res = command.execute(event);
   if (res.type = Event::ERROR)
       return false;
   return true;
}



bool GameFacade::clicked(int x, int y){
    Event event, res;

    if (game->getBaseActive()==false && game->getUnitActive()==false){
        ClickedCommand command(field, x, y);
        event.type = Event::CLICKED;
        event.coord.x = x; event.coord.y = y;
        res = command.execute(event);
        if (res.type==Event::ERROR)
             return false;
        if (res.type==Event::UNIT_INFO){
            game->setUnitActive(true);
            game->setInfoMessage(res);
            buffX = x; buffY = y;
        }
        else if (res.type==Event::BASE_INFO){
            game->setBaseActive(true);
            game->setInfoMessage(res);
            buffX = x; buffY = y;
        }
        return true;

    }

    else if (game->getUnitActive()){
        ClickedCommand command(field, x, y);
        event.type = Event::UNIT_ACTION;
        event.coord.x = buffX; event.coord.y = buffY;
        event = command.execute(event);
        if (event.type==Event::ERROR)
            return false;
        else {
            game->setInactive();
            return true;
        }
    }

    else if (game->getBaseActive()){
        ClickedCommand command(field, buffX, buffY);
        event.type = Event::UNIT_CREATE;
        if ((x>=0 && x<=1)&&(y==16||y==17)){
            event.unitType = Event::WARRIOR;
        }
        else if ((x>1 && x<=2)&&(y==16||y==17)){
            event.unitType = Event::MAGIC;
        }
        else if ((x>2 && x<=3)&&(y==16||y==17)){
            event.unitType = Event::SIEGE;
        }
        else if ((x>3 && x<=4)&&(y==16||y==17)){
            game->setInactive();
        }
        else {
            return false;
        }

        command.execute(event);
        game->setInactive();
        return true;
    }

    else {
        return false;
    }
}


GameFacade::GameFacade(GameField* field_, Game* game, BaseConstructor* baseConstructor)
    : field(field_), game(game), baseConstructor(baseConstructor), buffX(0), buffY(0)
{

}

















GameFacade::~GameFacade()
{

}

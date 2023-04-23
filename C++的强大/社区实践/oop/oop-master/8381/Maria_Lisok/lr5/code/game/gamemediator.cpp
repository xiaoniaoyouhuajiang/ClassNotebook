#include "gamemediator.h"
#include "Base/base.h"
#include "game.h"

GameMediator::GameMediator(Game *game, Base *base): game(game), base(base)
{
    base->setGameMediator(this);
}

void GameMediator::Notify(Unit *u, bool add)
{
    if(add)
        game->addUnit(u, base);
    else
        game->deleteUnit(u, base);
}


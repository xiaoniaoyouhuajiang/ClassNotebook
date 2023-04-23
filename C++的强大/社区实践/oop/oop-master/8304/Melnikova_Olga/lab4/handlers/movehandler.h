#ifndef MOVEHANDLER_H
#define MOVEHANDLER_H
#include "abstracthandler.h"

class MoveHandler : public AbstractHandler
{
public:
    Game* game;
    MoveHandler(Game* game){
        this->game = game;
    }
    bool Move(Unit* who, int x2, int y2) override {
        if(who->movementRadius >= abs(who->x + who->y - x2 - y2)){
            MoveUnit* commit = new MoveUnit(game, who->x, who->y, x2, y2);
            commit->Execute();
            game->isActionDone = true;
            return true;
        }else{
            return false;
        }
    }
};

#endif // MOVEHANDLER_H

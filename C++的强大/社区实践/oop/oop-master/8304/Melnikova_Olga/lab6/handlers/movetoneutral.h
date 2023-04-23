#ifndef MOVETONEUTRAL_H
#define MOVETONEUTRAL_H
#include "abstracthandler.h"

class MoveToNeutral : public AbstractHandler
{
public:
    Game<Rules>* game;
    MoveToNeutral(Game<Rules>* game){
        this->game = game;
    }
    bool MoveToNeutr(Unit* unit, NeutralObject* obj) override {
        if(unit->movementRadius >= abs(unit->x + unit->y - obj->x - obj->y)){
            MoveUnitToNeutral* commit = new MoveUnitToNeutral(game, unit, obj);
            commit->Execute();
            game->isActionDone = true;
            return true;
        }else{
            return false;
        }
    }
};

#endif // MOVETONEUTRAL_H

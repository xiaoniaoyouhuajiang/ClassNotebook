#ifndef MOVEUNITTONEUTRAL_H
#define MOVEUNITTONEUTRAL_H
#include "command.h"
#include "game.h"

class MoveUnitToNeutral : public Command
{
private:
    Game<Rules> *game_;
    Unit* unit;
    NeutralObject* obj;
public:
    MoveUnitToNeutral(Game<Rules> *game, Unit* unit, NeutralObject* obj) ;
    void Execute() const override {
        this->game_->moveToNeutral(unit, obj);
    }
};

#endif // MOVEUNITTONEUTRAL_H

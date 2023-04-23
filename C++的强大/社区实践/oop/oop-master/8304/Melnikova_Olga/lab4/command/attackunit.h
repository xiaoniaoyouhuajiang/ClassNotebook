#include "command.h"
#include "game.h"

class AttackUnit : public Command
{
private:
    Game *game_;
    Unit* who_;
    Object* whom_;
public:
    AttackUnit(Game *game, Unit* who, Object* whom);
    void Execute() const override {
        this->game_->atack(who_, whom_);
    }
};

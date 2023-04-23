#include "command.h"
#include "game.h"

class AttackUnit : public Command
{
private:
    Game<Rules> *game_;
    Unit* who_;
    Object* whom_;
public:
    AttackUnit(Game<Rules> *game, Unit* who, Object* whom);
    void Execute() const override {
        this->game_->atack(who_, whom_);
    }
};

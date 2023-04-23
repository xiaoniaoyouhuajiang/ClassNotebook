#include "command.h"
#include "game.h"

class MoveUnit : public Command
{
private:
    Game<Rules> *game_;
    int x1_;
    int y1_;
    int x2_;
    int y2_;
public:
    MoveUnit(Game<Rules> *game, int x1_, int y1_, int x2_, int y2_) ;
    void Execute() const override {
        this->game_->move(x1_, y1_, x2_, y2_);
    }
};


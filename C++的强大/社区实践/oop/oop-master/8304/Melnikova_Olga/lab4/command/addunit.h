#include "command.h"
#include "game.h"

class AddUnit : public Command
{
private:
    Game *game_;
    std::string who_;
    bool numBase_;
    int x_;
    int y_;
public:
    AddUnit(Game *game, std::string who, bool numBase, int x, int y) ;
    void Execute() const override {
        this->game_->add(who_, numBase_, x_, y_);
    }
};


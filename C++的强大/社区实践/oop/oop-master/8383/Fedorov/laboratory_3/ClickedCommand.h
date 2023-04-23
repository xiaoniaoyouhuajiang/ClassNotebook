#ifndef CLICKEDCOMMAND_H
#define CLICKEDCOMMAND_H
#include "Command.h"
class GameField;


class ClickedCommand : public Command
{
private:
    GameField* field;
    int cellX;
    int cellY;
public:
    Event execute(Event) override;
    ClickedCommand(GameField*,int,int);
    virtual ~ClickedCommand();
};

#endif // CLICKEDCOMMAND_H

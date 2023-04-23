#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H
#include "Command.h"
class Unit;


class MoveCommand : public Command
{
private:
    Unit* unit;
    int destX;
    int destY;
public:
    MoveCommand(Unit*, int, int);
    Event execute(Event) override;
    virtual ~MoveCommand();
};

#endif // MOVECOMMAND_H

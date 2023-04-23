#ifndef FIELDCOMMAND_H
#define FIELDCOMMAND_H
#include "Command.h"
class GameField;

class FieldCommand : public Command
{
private:
    GameField* field;
    int coordX;
    int coordY;
public:
    FieldCommand(GameField*, int, int);
    Event execute(Event) override;
    virtual ~FieldCommand();
};

#endif // FIELDCOMMAND_H

#ifndef UNITINFOCOMMAND_H
#define UNITINFOCOMMAND_H
#include "Command.h"
class Unit;

class UnitInfoCommand : public Command
{
private:
Unit* unit;
public:
    Event execute(Event ev) override;
    UnitInfoCommand(Unit* unit);
    virtual ~UnitInfoCommand();
};

#endif // UNITINFOCOMMAND_H

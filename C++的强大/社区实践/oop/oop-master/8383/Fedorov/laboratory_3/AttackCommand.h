#ifndef ATTACKCOMMAND_H
#define ATTACKCOMMAND_H
#include "Command.h"
class Unit;



class AttackCommand : public Command
{
private:
   Unit* attacker;
public:
    AttackCommand(Unit*);
    Event execute(Event) override;
    virtual ~AttackCommand();
};

#endif // ATTACKCOMMAND_H

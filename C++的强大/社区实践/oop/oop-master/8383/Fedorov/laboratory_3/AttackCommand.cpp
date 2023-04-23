#include "AttackCommand.h"
#include "Unit.h"




AttackCommand::AttackCommand(Unit* unit)
   : attacker(unit)
{}


Event AttackCommand::execute(Event event){
    Event result;
    if (event.type==Event::ATTACK && attacker){
        bool res = attacker->attack(event.attackCoord.x, event.attackCoord.y);
        if (res==false) result.type = Event::ERROR;
        else result = event;
    }
    else {
        result.type = Event::ERROR;
    }
    return result;
}





AttackCommand::~AttackCommand()
{

}

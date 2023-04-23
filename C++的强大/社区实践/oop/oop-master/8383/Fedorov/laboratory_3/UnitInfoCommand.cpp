#include "UnitInfoCommand.h"
#include "Unit.h"


Event UnitInfoCommand::execute(Event ev){
    if (unit && ev.type==Event::UNIT_INFO){
        Event event = unit->getInfo();
        return event;
    }
    else {
        Event event;
        event.type = Event::ERROR;
        return event;
    }
}


UnitInfoCommand::UnitInfoCommand(Unit* unit)
    :unit(unit) {}


UnitInfoCommand::~UnitInfoCommand()
{

}

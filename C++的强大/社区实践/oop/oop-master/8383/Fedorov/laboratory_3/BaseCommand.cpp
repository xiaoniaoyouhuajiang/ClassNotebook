#include "BaseCommand.h"
#include "Base.h"


Event BaseCommand::execute(Event event){
    Event result;
    if (base && event.type==Event::BASE_INFO){
        result = base->getInfo();
        return result;
    }
    else if (event.type==Event::UNIT_CREATE && base){
        Unit* un = base->createUnit(event);
        if (un) return event;
    }
    else{
        result.type = Event::ERROR;
        return result;
    }
    result.type=Event::ERROR;
    return result;
}



BaseCommand::BaseCommand(Base* base)
    : base(base) {}




BaseCommand::~BaseCommand()
{

}

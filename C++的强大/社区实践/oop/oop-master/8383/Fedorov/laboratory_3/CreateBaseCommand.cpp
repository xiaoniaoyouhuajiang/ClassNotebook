#include "CreateBaseCommand.h"
#include "BaseConstructor.h"
#include "Base.h"




Event CreateBaseCommand::execute(Event event)
{
   Base* newBase = constructor->createBase(event);
   if (newBase){
       Event ev = newBase->getInfo();
       return ev;
   }
   else{
       Event retEvent;
       retEvent.type = Event::ERROR;
       return retEvent;
   }
}




CreateBaseCommand::CreateBaseCommand(BaseConstructor* constr)
    : constructor(constr) {}


CreateBaseCommand::~CreateBaseCommand()
{

}

#ifndef COMMAND_H
#define COMMAND_H
#include "Event.h"

class Command
{
  public:
   virtual ~Command() {}
   virtual Event execute(Event) = 0;
};

#endif // COMMAND_H

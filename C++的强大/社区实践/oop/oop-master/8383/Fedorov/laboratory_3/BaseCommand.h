#ifndef BASECOMMAND_H
#define BASECOMMAND_H
#include "Command.h"
class Base;

class BaseCommand : public Command
{
 private:
   Base* base;
 public:
   Event execute(Event) override;
   BaseCommand(Base*);
   virtual ~BaseCommand();
};
#endif // BASECOMMAND_H

#ifndef CREATEBASECOMMAND_H
#define CREATEBASECOMMAND_H

#include "Command.h"

class BaseConstructor;

class CreateBaseCommand : public Command
{
private:
BaseConstructor* constructor;
public:
    virtual Event execute(Event) override;
    CreateBaseCommand(BaseConstructor* constr);
    virtual ~CreateBaseCommand();
};
#endif // CREATEBASECOMMAND_H

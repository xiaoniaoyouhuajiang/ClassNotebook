#ifndef LAB2_INVOKER_H
#define LAB2_INVOKER_H

#include "Command.h"
class Command;
class Invoker {
private:
    std::shared_ptr<Command> command = nullptr;
public:
    Invoker() = default;
    void set_command(std::shared_ptr<Command> command);
    void execute() const;
};


#endif

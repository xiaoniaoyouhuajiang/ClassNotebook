#include "Invoker.h"

void Invoker::set_command(std::shared_ptr<Command> command) {
    this->command = command;
}

void Invoker::execute() const {
    command->execute();
}

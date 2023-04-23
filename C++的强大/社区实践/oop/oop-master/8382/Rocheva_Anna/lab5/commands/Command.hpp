#ifndef LABOOP_COMMAND_HPP
#define LABOOP_COMMAND_HPP

#include "../GameField.hpp"
#include "../loggers/LogProxy.hpp"
#include "../loggers/Adapter.hpp"

class Command{
public:
    virtual ~Command(){};
    virtual void execute(GameField *gameField, Base *base, LogProxy *logger) = 0;
};



#endif //LABOOP_COMMAND_HPP

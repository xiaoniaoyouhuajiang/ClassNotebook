#ifndef LABOOP_COMMAND_HPP
#define LABOOP_COMMAND_HPP

#include "../loggers/LogProxy.hpp"
#include "../loggers/Adapter.hpp"
#include "../rules//Rules.hpp"
#include <cmath>

class Command{
public:
    virtual ~Command(){};
    virtual void execute(GameField *gameField, Base *base, LogProxy *logger, Base *enemyBase) = 0;
};



#endif //LABOOP_COMMAND_HPP

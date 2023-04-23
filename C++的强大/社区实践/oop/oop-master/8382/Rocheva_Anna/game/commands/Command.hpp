#ifndef LABOOP_COMMAND_HPP
#define LABOOP_COMMAND_HPP

#include "../GameField.hpp"

class Command{
public:
    virtual ~Command(){};
    virtual void execute(GameField *gameField) = 0;
private:

};



#endif //LABOOP_COMMAND_HPP

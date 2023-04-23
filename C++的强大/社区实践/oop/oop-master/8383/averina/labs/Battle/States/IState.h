#ifndef OOP_ISTATE_H
#define OOP_ISTATE_H

#include <string>
#include "../../Interface/Links/Chain.h"

class IState
{
public:
    virtual void playerCommand(std::string command, Chain *player) = 0;
};



#endif //OOP_ISTATE_H

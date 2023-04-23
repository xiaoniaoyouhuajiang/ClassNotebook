//
// Created by Artem Butko on 24.05.2020.
//

#ifndef OOP_NEW_ISTATE_H
#define OOP_NEW_ISTATE_H


#include <string>
#include "../../ChainOfResponsibility/Chain.h"

class IState
{
public:
    virtual void playerCommand(std::string command, Chain *player) = 0;
};


#endif //OOP_NEW_ISTATE_H

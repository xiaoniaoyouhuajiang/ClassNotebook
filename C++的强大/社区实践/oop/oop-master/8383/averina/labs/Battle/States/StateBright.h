//
// Created by olyaave on 01.06.2020.
//

#ifndef OOP_STATEBRIGHT_H
#define OOP_STATEBRIGHT_H


#include "IState.h"

class StateBright : public IState
{
public:
    void playerCommand(std::string command, Chain *player) override;
};



#endif //OOP_STATEBRIGHT_H

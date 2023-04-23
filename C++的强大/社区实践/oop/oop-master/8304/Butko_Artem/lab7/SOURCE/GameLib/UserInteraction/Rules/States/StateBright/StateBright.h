//
// Created by Artem Butko on 27.05.2020.
//

#ifndef OOP_NEW_STATEBRIGHT_H
#define OOP_NEW_STATEBRIGHT_H


#include "../IState.h"

class StateBright : public IState
{
public:
    void playerCommand(std::string command, Chain *player) override;
};


#endif //OOP_NEW_STATEBRIGHT_H

//
// Created by Artem Butko on 28.05.2020.
//

#ifndef OOP_NEW_STATEUNDEAD_H
#define OOP_NEW_STATEUNDEAD_H


#include "../IState.h"

class StateUndead : public IState
{
public:
    void playerCommand(std::string command, Chain *player) override;
};


#endif //OOP_NEW_STATEUNDEAD_H

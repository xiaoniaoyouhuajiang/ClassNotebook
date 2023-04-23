
#ifndef OOP_STATEUNDEAD_H
#define OOP_STATEUNDEAD_H


#include "IState.h"

class StateUndead : public IState
{
public:
    void playerCommand(std::string command, Chain *player) override;
};


#endif //OOP_STATEUNDEAD_H

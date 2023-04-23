
#ifndef OOP_STATEDARK_H
#define OOP_STATEDARK_H

#include "IState.h"


class StateDark : public IState
{
public:
    void playerCommand(std::string command, Chain *player) override;
};

#endif //OOP_STATEDARK_H


#ifndef OOP_ATTACKUNITREQUEST_H
#define OOP_ATTACKUNITREQUEST_H


#include "../IRequest.h"

/*
 * AttackUnitRequest -- класс-команда атаки юнитом противника.
 */

class AttackUnitRequest : public IRequest
{
public:
    AttackUnitRequest(Field* field, std::string player) : IRequest(field) { this->player = player;};
    void Command() override ;
private:
    int x, y, i, j;
};

#endif //OOP_ATTACKUNITREQUEST_H

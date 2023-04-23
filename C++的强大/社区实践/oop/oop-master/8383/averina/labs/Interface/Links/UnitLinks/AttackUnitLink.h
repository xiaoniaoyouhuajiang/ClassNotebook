#ifndef OOP_ATTACKUNITLINK_H
#define OOP_ATTACKUNITLINK_H

#include "../Chain.h"
#include "../../Commands/IRequest.h"

/*
 * AttackUnitLink -- класс-звено цепи для атаки юнитом противника.
 */

class AttackUnitLink : public Chain
{
public:
    AttackUnitLink(Field* field) : Chain(field) {};
    void chain(std::string command, std::string player) override;
};

#endif //OOP_ATTACKUNITLINK_H

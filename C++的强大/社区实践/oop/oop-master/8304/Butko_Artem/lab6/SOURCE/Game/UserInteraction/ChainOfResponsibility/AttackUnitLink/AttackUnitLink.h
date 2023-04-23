//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_ATTACKUNITLINK_H
#define OOP_NEW_ATTACKUNITLINK_H


#include "../Chain.h"

/*
 * AttackUnitLink -- класс-звено цепи для атаки юнитом противника.
 */

class AttackUnitLink : public Chain
{
public:
    AttackUnitLink(Field* field) : Chain(field) {};
    void chain(std::string command, std::string player) override;
};


#endif //OOP_NEW_ATTACKUNITLINK_H

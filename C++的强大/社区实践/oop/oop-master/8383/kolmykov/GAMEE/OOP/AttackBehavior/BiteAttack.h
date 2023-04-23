#ifndef BITEATTACK_H
#define BITEATTACK_H
#include "Unit.h"


class BiteAttack : public AttackBehavior
{
public:
    BiteAttack();
    void attack(std::shared_ptr<Unit> unit);
};

#endif // BITEATTACK_H

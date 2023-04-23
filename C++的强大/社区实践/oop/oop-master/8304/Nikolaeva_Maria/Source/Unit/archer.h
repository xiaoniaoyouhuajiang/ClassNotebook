#ifndef ARCHER_H
#define ARCHER_H

#include "Unit/standingunit.h"


class Archer : public StandingUnit
{
public:
    Archer(Mediator* mediator);
    ~Archer();

    void regeneration() override;

    Unit* clone() override;

    char draw() override;
};

#endif // ARCHER_H

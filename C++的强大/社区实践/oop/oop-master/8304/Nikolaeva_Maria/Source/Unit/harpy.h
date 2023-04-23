#ifndef HARPY_H
#define HARPY_H

#include "Unit/flyingunit.h"


class Harpy : public FlyingUnit
{
public:
    Harpy(Mediator* mediator);
    ~Harpy();

    void regeneration() override;

    Unit* clone() override;

    char draw() override;
};

#endif // HARPY_H

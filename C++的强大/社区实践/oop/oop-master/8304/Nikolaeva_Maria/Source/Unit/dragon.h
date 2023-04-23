#ifndef DRAGON_H
#define DRAGON_H

#include "Unit/flyingunit.h"


class Dragon : public FlyingUnit
{
public:
    Dragon(Mediator* mediator);
    ~Dragon();

    void regeneration() override;

    Unit* clone() override;

    char draw() override;
};

#endif // DRAGON_H

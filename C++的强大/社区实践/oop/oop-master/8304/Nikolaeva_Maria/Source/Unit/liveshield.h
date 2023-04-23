#ifndef LIVESHIELD_H
#define LIVESHIELD_H

#include "Unit/standingunit.h"


class LiveShield : public StandingUnit
{
public:
    LiveShield(Mediator* mediator);
    ~LiveShield();

    void regeneration() override;

    Unit* clone() override;

    char draw() override;
};

#endif // LIVESHIELD_H

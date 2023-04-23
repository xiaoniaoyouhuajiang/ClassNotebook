#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "Unit/infantryunit.h"


class Swordsman : public InfantryUnit
{
public:
    Swordsman(Mediator* mediator);
    ~Swordsman();

    void regeneration() override;

    Unit* clone() override;

    char draw() override;
};

#endif // SWORDSMAN_H

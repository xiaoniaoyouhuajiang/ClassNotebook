#ifndef DWARF_H
#define DWARF_H

#include "Unit/infantryunit.h"


class Dwarf : public InfantryUnit
{
public:
    Dwarf(Mediator* mediator);
    ~Dwarf();

    void regeneration() override;

    Unit* clone() override;

    char draw() override;
};

#endif // DWARF_H

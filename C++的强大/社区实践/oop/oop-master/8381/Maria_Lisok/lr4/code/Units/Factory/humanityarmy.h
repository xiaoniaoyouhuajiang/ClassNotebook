#ifndef HUMANITYARMY_H
#define HUMANITYARMY_H

#include "abstractArmy.h"

#include <Units/Arrow/archer.h>

#include <Units/Cavelry/knigth.h>

#include <Units/Infantry/swardman.h>


class HumanityArmy: public AbstractArmy{
public:
    Arrow* createArrow();
    Cavelry* createCavelry();
    Infantry* createInfantry();
};

#endif // HUMANITYARMY_H

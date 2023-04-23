#ifndef ABSTRACTARMY_H
#define ABSTRACTARMY_H

#include <Units/Arrow/arrow.h>
#include <Units/Cavelry/cavelry.h>
#include <Units/Infantry/infantry.h>

class AbstractArmy{
public:
    virtual ~AbstractArmy()=default;
    virtual Arrow* createArrow()=0;
    virtual Cavelry* createCavelry()=0;
    virtual Infantry* createInfantry()=0;
};
#endif // ABSTRACTARMY_H

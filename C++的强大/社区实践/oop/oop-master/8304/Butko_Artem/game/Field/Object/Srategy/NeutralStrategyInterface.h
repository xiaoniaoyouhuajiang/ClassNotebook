



#ifndef NEW_LR1_NEUTRALSTRATEGYINTERFACE_H
#define NEW_LR1_NEUTRALSTRATEGYINTERFACE_H


#include "../Unit/Unit.h"

class NeutralStrategyInterface
{
public:
    virtual void unitImpact(Unit* unit_) = 0;
};


#endif //NEW_LR1_NEUTRALSTRATEGYINTERFACE_H

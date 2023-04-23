



#ifndef NEW_LR1_HEALTHUP_H
#define NEW_LR1_HEALTHUP_H


#include "../NeutralStrategyInterface.h"

class HealthUp : public NeutralStrategyInterface
{
public:
    void unitImpact(Unit* unit_) override;
};


#endif //NEW_LR1_HEALTHUP_H



//

#ifndef NEW_LR1_HEALTHDOWN_H
#define NEW_LR1_HEALTHDOWN_H


#include "../NeutralStrategyInterface.h"

class HealthDown : public NeutralStrategyInterface
{
public:
    void unitImpact(Unit* unit_) override;
};


#endif //NEW_LR1_HEALTHDOWN_H

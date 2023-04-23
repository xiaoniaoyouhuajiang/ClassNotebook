//

//

#ifndef NEW_LR1_HOLYUP_H
#define NEW_LR1_HOLYUP_H


#include "../NeutralStrategyInterface.h"

class HolyUp : public NeutralStrategyInterface
{
public:
    void unitImpact(Unit* unit_) override;
};


#endif //NEW_LR1_HOLYUP_H

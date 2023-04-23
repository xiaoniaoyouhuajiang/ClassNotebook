



#ifndef NEW_LR1_ARMORUP_H
#define NEW_LR1_ARMORUP_H


#include "../NeutralStrategyInterface.h"

class ArmorUp : public NeutralStrategyInterface
{
public:
    void unitImpact(Unit* unit_) override;
};


#endif //NEW_LR1_ARMORUP_H

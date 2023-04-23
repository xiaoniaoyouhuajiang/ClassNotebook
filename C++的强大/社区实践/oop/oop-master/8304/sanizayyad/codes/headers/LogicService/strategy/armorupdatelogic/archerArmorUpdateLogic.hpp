#ifndef archerArmorUpdateLogic_hpp
#define archerArmorUpdateLogic_hpp

#include "armorupdatelogic.hpp"

#include <stdio.h>

class ArcherArmorUpdateLogic : public ArmorUpdateLogic
{
public:
    
    virtual void updateUnit(std::shared_ptr<unit::Unit> unit) const override;
    virtual std::shared_ptr<StrategyPattern> clone() const override;

};

#endif /* archerArmorUpdateLogic_hpp */

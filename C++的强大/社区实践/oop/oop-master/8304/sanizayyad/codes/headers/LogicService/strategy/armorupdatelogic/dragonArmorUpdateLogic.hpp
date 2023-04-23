#ifndef dragonArmorUpdateLogic_hpp
#define dragonArmorUpdateLogic_hpp

#include "armorupdatelogic.hpp"

#include <stdio.h>

class DragonArmorUpdateLogic : public ArmorUpdateLogic
{
public:
    
    virtual void updateUnit(std::shared_ptr<unit::Unit> unit) const override;
    virtual std::shared_ptr<StrategyPattern> clone() const override;

};
#endif /* dragonArmorUpdateLogic_hpp */

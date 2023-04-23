#ifndef SpearManArmorUpdateLogic_hpp
#define SpearManArmorUpdateLogic_hpp

#include "armorupdatelogic.hpp"

#include <stdio.h>

class SpearManArmorUpdateLogic : public ArmorUpdateLogic
{
public:
    
    virtual void updateUnit(std::shared_ptr<unit::Unit> unit) const override;
    virtual std::shared_ptr<StrategyPattern> clone() const override;
};
#endif /* SpearManArmorUpdateLogic_hpp */

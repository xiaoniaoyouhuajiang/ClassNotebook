#ifndef SwordManArmorUpdateLogic_hpp
#define SwordManArmorUpdateLogic_hpp

#include "armorupdatelogic.hpp"

#include <stdio.h>

class SwordManArmorUpdateLogic : public ArmorUpdateLogic
{
public:
        
    virtual void updateUnit(std::shared_ptr<unit::Unit> unit) const override;
    virtual std::shared_ptr<StrategyPattern> clone() const override;

};

#endif /* SwordManArmorUpdateLogic_hpp */

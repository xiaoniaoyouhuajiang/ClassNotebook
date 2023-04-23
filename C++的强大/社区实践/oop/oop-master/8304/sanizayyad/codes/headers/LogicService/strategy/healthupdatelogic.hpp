#ifndef healthupdatelogic_hpp
#define healthupdatelogic_hpp

#include "strategy.hpp"

#include <stdio.h>

class HealthUpdateLogic : public StrategyPattern
{
public:
  
     virtual void updateUnit(std::shared_ptr<unit::Unit> unit) const override;
     virtual std::shared_ptr<StrategyPattern> clone() const override;
    
};
#endif /* healthupdatelogic_hpp */

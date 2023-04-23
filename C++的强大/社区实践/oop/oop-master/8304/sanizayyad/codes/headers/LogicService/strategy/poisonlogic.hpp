#ifndef poisonlogic_hpp
#define poisonlogic_hpp

#include "strategy.hpp"

#include <stdio.h>

class PoisonLogic : public StrategyPattern
{
public:
  
     virtual void updateUnit(std::shared_ptr<unit::Unit> unit) const override;
     virtual std::shared_ptr<StrategyPattern> clone() const override;

    
};
#endif /* poisonlogic_hpp */

#ifndef strategy_hpp
#define strategy_hpp

#include "unit.hpp"

#include <stdio.h>


class StrategyPattern
{
public:
    virtual ~StrategyPattern() = default;

    virtual void updateUnit(std::shared_ptr<unit::Unit> unit) const = 0;

    virtual std::shared_ptr<StrategyPattern> clone() const  = 0;

};

#endif /* damagerecoverylogic_hpp */

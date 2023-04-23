#ifndef nologic_hpp
#define nologic_hpp

#include "strategy.hpp"

#include <stdio.h>

class NoLogic : public StrategyPattern
{
public:
    
    virtual void updateUnit(std::shared_ptr<unit::Unit> unit) const override;
    virtual std::shared_ptr<StrategyPattern> clone() const override;

    
};
#endif /* nologic_hpp */

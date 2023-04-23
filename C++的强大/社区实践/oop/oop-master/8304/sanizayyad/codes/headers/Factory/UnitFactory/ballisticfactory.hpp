#ifndef ballisticfactory_hpp
#define ballisticfactory_hpp

#include "unitfactory.hpp"

#include <stdio.h>

namespace unit {
class BallisticFactory : public UnitFactory
{
public:
   
    virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) const override;

};}



#endif /* ballisticfactory_hpp */

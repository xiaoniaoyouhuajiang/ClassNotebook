#ifndef vampirefactory_hpp
#define vampirefactory_hpp

#include "unitfactory.hpp"

#include <stdio.h>

namespace unit {
class VampireFactory : public UnitFactory
{
public:
  

     virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) const override;

};
}


#endif /* vampirefactory_hpp */

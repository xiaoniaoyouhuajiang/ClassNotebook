#ifndef dragonfactory_hpp
#define dragonfactory_hpp

#include "unitfactory.hpp"

#include <stdio.h>

namespace unit {
class DragonFactory : public UnitFactory
{
public:
  
     virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) const override;


};

}


#endif /* dragonfactory_hpp */

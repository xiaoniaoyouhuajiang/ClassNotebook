#ifndef swordmanfactory_hpp
#define swordmanfactory_hpp

#include "unitfactory.hpp"

#include <stdio.h>

namespace unit {
class SwordManFactory : public UnitFactory
{
public:
    
    virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) const override;
    
};
}



#endif /* swordmanfactory_hpp */

#ifndef spearmanfactory_hpp
#define spearmanfactory_hpp

#include "unitfactory.hpp"

#include <stdio.h>

namespace unit {
class SpearManFactory : public UnitFactory
{
public:
    
    virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) const override;


};
}


#endif /* spearmanfactory_hpp */

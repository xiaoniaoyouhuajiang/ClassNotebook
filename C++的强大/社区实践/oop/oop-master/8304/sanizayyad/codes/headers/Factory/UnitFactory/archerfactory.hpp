#ifndef archerfactory_hpp
#define archerfactory_hpp

#include "unitfactory.hpp"

#include <stdio.h>

namespace unit {
class ArcherFactory : public UnitFactory
{
public:
   
    virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) const override;

};}


#endif /* archerfactory_hpp */

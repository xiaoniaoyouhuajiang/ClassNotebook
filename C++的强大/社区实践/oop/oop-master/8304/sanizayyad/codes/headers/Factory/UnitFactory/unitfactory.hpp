
#ifndef unitfactory_hpp
#define unitfactory_hpp

#include "unit.hpp"
#include "swordman.hpp"
#include "spearman.hpp"
#include "archer.hpp"
#include "ballistic.hpp"
#include "vampire.hpp"
#include "dragon.hpp"

#include <stdio.h>
#include <memory>

namespace unit {
class UnitFactory
{
public:

    virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) const = 0;

};}




#endif /* unitfactory_hpp */

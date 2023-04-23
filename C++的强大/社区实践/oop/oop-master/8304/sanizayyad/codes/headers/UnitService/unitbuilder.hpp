#ifndef unitbuilder_hpp
#define unitbuilder_hpp

#include "unitfactory.hpp"
#include "armorfactory.hpp"
#include "weaponfactory.hpp"

#include <stdio.h>
#include <memory>

namespace unit {
class UnitBuilder
{
public:
    UnitBuilder(const Position2D& position);
    void reset();

    void setMediator(std::shared_ptr<Mediator> mediator);
    void setArmorFactory(std::shared_ptr<ArmorFactory> armorFactory);
    void setWeaponFactory(std::shared_ptr<WeaponFactory> weaponFactory);
    void setUnitFactory(std::shared_ptr<UnitFactory> unitFactory);
    void setPosition(const Position2D& position);
    void setHealthPoints(double healthPoints);
    std::shared_ptr<Unit> getUnit();

private:
    std::shared_ptr<Mediator> mediator;
    std::shared_ptr<UnitFactory> unitFactory;
    std::shared_ptr<WeaponFactory> weaponFactory;
    std::shared_ptr<ArmorFactory> armorFactory;
    double healthPoints;
    Position2D position;

};}



#endif /* unitbuilder_hpp */

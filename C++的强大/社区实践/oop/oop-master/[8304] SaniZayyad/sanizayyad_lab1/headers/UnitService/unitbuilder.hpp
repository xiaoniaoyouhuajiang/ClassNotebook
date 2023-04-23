#ifndef unitbuilder_hpp
#define unitbuilder_hpp

#include "unitfactory.hpp"
#include "armorfactory.hpp"
#include "weaponfactory.hpp"

#include <stdio.h>

class UnitBuilder
{
public:
    UnitBuilder(const Position2D& position);
    void reset();

    void setMediator(std::shared_ptr<Mediator> mediator);
    void setArmorFactory(std::unique_ptr<ArmorFactory> armorFactory);
    void setWeaponFactory(std::unique_ptr<WeaponFactory> weaponFactory);
    void setUnitFactory(std::unique_ptr<UnitFactory> unitFactory);
    void setPosition(const Position2D& position);

    std::shared_ptr<Unit> getUnit();

private:
    std::shared_ptr<Mediator> mediator;
    std::unique_ptr<UnitFactory> unitFactory;
    std::unique_ptr<WeaponFactory> weaponFactory;
    std::unique_ptr<ArmorFactory> armorFactory;
    Position2D position;
};


#endif /* unitbuilder_hpp */

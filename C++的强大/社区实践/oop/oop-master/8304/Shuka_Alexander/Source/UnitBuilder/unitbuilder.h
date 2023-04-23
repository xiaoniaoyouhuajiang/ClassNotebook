#ifndef UNITBUILDER_H
#define UNITBUILDER_H

#include <memory>

#include "Unit/unit.h"

#include "Factory/ArmorFactory/armorfactory.h"
#include "Factory/WeaponFactory/weaponfactory.h"
#include "Factory/UnitFactory/unitfactory.h"


namespace unit {
class UnitBuilder
{
public:
    UnitBuilder(const Point2D& point);
    void reset();

    void setArmorFactory(std::shared_ptr<ArmorFactory> armorFactory);
    void setMediator(std::shared_ptr<Mediator> mediator);
    void setWeaponFactory(std::shared_ptr<WeaponFactory> weaponFactory);
    void setUnitFactory(std::shared_ptr<UnitFactory> unitFactory);
    void setPosition(const Point2D& point);
    void setHealthPoints(double healthPoints);

    std::shared_ptr<Unit> getUnit();

private:
    std::shared_ptr<Mediator> mediator;
    std::shared_ptr<UnitFactory> unitFactory;
    std::shared_ptr<WeaponFactory> weaponFactory;
    std::shared_ptr<ArmorFactory> armorFactory;
    double healthPoints;
    Point2D point;
};
}

#endif // UNITBUILDER_H

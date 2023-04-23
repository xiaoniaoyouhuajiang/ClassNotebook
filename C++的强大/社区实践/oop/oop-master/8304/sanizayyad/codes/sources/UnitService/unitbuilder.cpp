#include "unitbuilder.hpp"

using namespace unit;

UnitBuilder::UnitBuilder(const Position2D& position) : position(position)
{

}


void UnitBuilder::reset()
{
    unitFactory.reset();
    weaponFactory.reset();
    armorFactory.reset();
}


void UnitBuilder::setArmorFactory(std::shared_ptr<ArmorFactory> armorFactory)
{
    this->armorFactory = armorFactory;
}


void UnitBuilder::setMediator(std::shared_ptr<Mediator> mediator)
{
    this->mediator = mediator;
}


void UnitBuilder::setWeaponFactory(std::shared_ptr<WeaponFactory> weaponFactory)
{
    this->weaponFactory = weaponFactory;
}

void UnitBuilder::setHealthPoints(double healthPoints)
{
    this->healthPoints = healthPoints;
}

void UnitBuilder::setUnitFactory(std::shared_ptr<UnitFactory> unitFactory)
{
    this->unitFactory = unitFactory;
}


void UnitBuilder::setPosition(const Position2D& position)
{
    this->position = position;
}

std::shared_ptr<Unit> UnitBuilder::getUnit()
{
    std::shared_ptr<Unit> unit = unitFactory->createUnit(position,mediator);
    unit->setArmor(armorFactory->createArmor());
    unit->setWeapon(weaponFactory->createWeapon());
    if (this->healthPoints != __DBL_MIN__) {
        unit->healthPoints = this->healthPoints;
    }
    
    return unit;
}

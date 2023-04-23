#include "unitcreator.hpp"

using namespace unit;


std::shared_ptr<Unit> UnitCreator::createSwordMan(const Position2D& position,std::shared_ptr<Mediator> mediator,double healthPoints)
{
    UnitBuilder builder(position);

    std::shared_ptr<UnitFactory> unitFactory(new SwordManFactory);
    std::shared_ptr<ArmorFactory> armorFactory(new MediumArmorFactory);
    std::shared_ptr<WeaponFactory> weaponFactory(new SwordWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    builder.setMediator(mediator);
    builder.setHealthPoints(healthPoints);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitCreator::createSpearMan(const Position2D& position,std::shared_ptr<Mediator> mediator,double healthPoints)
{
    UnitBuilder builder(position);

    std::shared_ptr<UnitFactory> unitFactory(new SpearManFactory);
    std::shared_ptr<ArmorFactory> armorFactory(new MediumArmorFactory);
    std::shared_ptr<WeaponFactory> weaponFactory(new SpearWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    builder.setMediator(mediator);
    builder.setHealthPoints(healthPoints);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitCreator::createArcher(const Position2D& position,std::shared_ptr<Mediator> mediator,double healthPoints)
{
    UnitBuilder builder(position);

    std::shared_ptr<UnitFactory> unitFactory(new ArcherFactory);
    std::shared_ptr<ArmorFactory> armorFactory(new LightArmorFactory);
    std::shared_ptr<WeaponFactory> weaponFactory(new ArrowWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    builder.setMediator(mediator);
    builder.setHealthPoints(healthPoints);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitCreator:: createBallistic(const Position2D& position,std::shared_ptr<Mediator> mediator,double healthPoints)
{
    UnitBuilder builder(position);

    std::shared_ptr<UnitFactory> unitFactory(new BallisticFactory);
    std::shared_ptr<ArmorFactory> armorFactory(new HeavyArmorFactory);
    std::shared_ptr<WeaponFactory> weaponFactory(new BallisticWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    builder.setMediator(mediator);
    builder.setHealthPoints(healthPoints);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitCreator::createVampire(const Position2D& position,std::shared_ptr<Mediator> mediator,double healthPoints)
{
    UnitBuilder builder(position);

    std::shared_ptr<UnitFactory> unitFactory(new VampireFactory);
    std::shared_ptr<ArmorFactory> armorFactory(new HeavyArmorFactory);
    std::shared_ptr<WeaponFactory> weaponFactory(new VampireTeethWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    builder.setMediator(mediator);
    builder.setHealthPoints(healthPoints);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitCreator::createDragon(const Position2D& position,std::shared_ptr<Mediator> mediator,double healthPoints)
{
    UnitBuilder builder(position);

    std::shared_ptr<UnitFactory> unitFactory(new DragonFactory);
    std::shared_ptr<ArmorFactory> armorFactory(new HeavyArmorFactory);
    std::shared_ptr<WeaponFactory> weaponFactory(new DragonFireWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    builder.setMediator(mediator);
    builder.setHealthPoints(healthPoints);

    return  builder.getUnit();
}

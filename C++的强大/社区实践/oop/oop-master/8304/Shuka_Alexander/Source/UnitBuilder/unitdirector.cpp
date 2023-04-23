#include "unitdirector.h"

using namespace unit;


std::shared_ptr<Unit> UnitDirector::createDragon(const Point2D& point,
                                                 std::shared_ptr<Mediator> mediator,
                                                 double healthPoints)
{
    UnitBuilder builder(point);

    builder.setUnitFactory(std::make_shared<DragonFactory>());
    builder.setArmorFactory(std::make_shared<MediumArmorFactory>());
    builder.setWeaponFactory(std::make_shared<MagicWeaponFactory>());
    builder.setMediator(mediator);
    builder.setHealthPoints(healthPoints);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitDirector::createThief(const Point2D& point,
                                                std::shared_ptr<Mediator> mediator,
                                                double healthPoints)
{
    UnitBuilder builder(point);

    builder.setUnitFactory(std::make_shared<ThiefFactory>());
    builder.setArmorFactory(std::make_shared<NoArmorFactory>());
    builder.setWeaponFactory(std::make_shared<SwordWeaponFactory>());
    builder.setMediator(mediator);
    builder.setHealthPoints(healthPoints);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitDirector::createWarrior(const Point2D& point,
                                                  std::shared_ptr<Mediator> mediator,
                                                  double healthPoints)
{
    UnitBuilder builder(point);

    builder.setUnitFactory(std::make_shared<WarriorFactory>());
    builder.setArmorFactory(std::make_shared<LightArmorFactory>());
    builder.setWeaponFactory(std::make_shared<SwordWeaponFactory>());
    builder.setMediator(mediator);
    builder.setHealthPoints(healthPoints);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitDirector::createTower(const Point2D& point,
                                                std::shared_ptr<Mediator> mediator,
                                                double healthPoints)
{
    UnitBuilder builder(point);

    builder.setUnitFactory(std::make_shared<TowerFactory>());
    builder.setArmorFactory(std::make_shared<MediumArmorFactory>());
    builder.setWeaponFactory(std::make_shared<BowWeaponFactory>());
    builder.setMediator(mediator);
    builder.setHealthPoints(healthPoints);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitDirector::createKamikadze(const Point2D& point,
                                                    std::shared_ptr<Mediator> mediator,
                                                    double healthPoints)
{
    UnitBuilder builder(point);

    builder.setUnitFactory(std::make_shared<KamikadzeFactory>());
    builder.setArmorFactory(std::make_shared<HeavyArmorFactory>());
    builder.setWeaponFactory(std::make_shared<MagicWeaponFactory>());
    builder.setMediator(mediator);
    builder.setHealthPoints(healthPoints);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitDirector::createGoldMiner(const Point2D& point,
                                                    std::shared_ptr<Mediator> mediator,
                                                    double healthPoints)
{
    UnitBuilder builder(point);

    builder.setUnitFactory(std::make_shared<GoldMinerFactory>());
    builder.setArmorFactory(std::make_shared<NoArmorFactory>());
    builder.setWeaponFactory(std::make_shared<NoWeaponFactory>());
    builder.setMediator(mediator);
    builder.setHealthPoints(healthPoints);

    return  builder.getUnit();
}

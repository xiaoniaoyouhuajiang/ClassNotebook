#include "towersettingstate.h"

TowerSettingState::TowerSettingState(Kind kind, int num, std::shared_ptr<Field> field, std::shared_ptr<Facade> facade) : State(kind, num, field, facade) {
    type = StateType::TOWER_SETTING_STATE;
}


TowerSettingState::~TowerSettingState() {

}


void TowerSettingState::create(int xT, int xU, UnitType type) {
    std::shared_ptr<UnitFactory> factory;
    switch(type) {
    case UnitType::BITING_ZOMBY:
        factory = std::shared_ptr<UnitFactory>(new BitingZombyFactory);
        break;
    case UnitType::HUMAN_ON_CAR:
        factory = std::shared_ptr<UnitFactory>(new HumanOnCarFactory);
        break;
    case UnitType::STINKY_ZOMBY:
        factory = std::shared_ptr<UnitFactory>(new StinkyZombyFactory);
        break;
    case UnitType::STRONG_ZOMBY:
        factory = std::shared_ptr<UnitFactory>(new StrongZombyFactory);
        break;
    case UnitType::HUMAN_ON_BIKE:
        factory = std::shared_ptr<UnitFactory>(new HumanOnBikeFactory);
        break;
    case UnitType::HUMAN_WITH_BAT:
        factory = std::shared_ptr<UnitFactory>(new HumanWithBatFactory);
        break;
    case UnitType::HUMAN_WITH_GUN:
        factory = std::shared_ptr<UnitFactory>(new HumanWithGunFactory);
        break;
    case UnitType::KAMIKADZE_ZOMBY:
        factory = std::shared_ptr<UnitFactory>(new KamikadzeZombyFactory);
        break;
    case UnitType::HUMAN_WITH_SWORD:
        factory = std::shared_ptr<UnitFactory>(new HumanWithSwordFactory);
        break;
    case UnitType::HUMAN_WITH_GRENADE:
        factory = std::shared_ptr<UnitFactory>(new HumanWithGrenadeFactory);
        break;
    case UnitType::SPIT_TO_AREA_ZOMBY:
        factory = std::shared_ptr<UnitFactory>(new SpitToAreaZombyFactory);
        break;
    case UnitType::SPIT_TO_ENEMY_ZOMBY:
        factory = std::shared_ptr<UnitFactory>(new SpitToEnemyZombyFactory);
        break;
    default:
        break;
    }
    if (kind == factory->getKind()) {
        facade->setTower(xT, yT, factory);
    }
}


void TowerSettingState::endStep(){

}

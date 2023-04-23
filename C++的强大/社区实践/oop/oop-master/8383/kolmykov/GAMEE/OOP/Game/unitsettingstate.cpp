#include "unitsettingstate.h"

UnitSettingState::UnitSettingState(Kind kind, int num, std::shared_ptr<Field> field, std::shared_ptr<Facade> facade) :State(kind, num, field, facade)
{
    type = StateType::UNIT_SETTING_STATE;
}


void UnitSettingState::create(int xT, int xU, UnitType type) {
    int y;
    switch(kind) {
    case Kind::ZOMBY:
        y = 0;
        break;
    case Kind::HUMAN:
        y = field->getHeight() - 1;
        break;
    }
    std::shared_ptr<Tower> tower = field->getCell(xT, y)->getTower();
    if (tower != nullptr) {
        int price;
        UnitType tmpType = tower->getFactory()->getType();
        if (tmpType == UnitType::BITING_ZOMBY || tmpType == UnitType::HUMAN_WITH_GUN || tmpType == UnitType::HUMAN_WITH_SWORD || tmpType == UnitType::SPIT_TO_ENEMY_ZOMBY) {
            price = 2;
        }
        else if(tmpType == UnitType::HUMAN_ON_CAR || tmpType == UnitType::HUMAN_ON_BIKE || tmpType == UnitType::STRONG_ZOMBY || tmpType == UnitType::KAMIKADZE_ZOMBY) {
            price = 3;
        }
        else {
            price = 1;
        }
        if (resources - price >= 0) {
            if (tower->getUnitCount() < tower->getSize()) {
                resources -= price;
                facade->create(xT, yT, xU, yU);
            }
        }
    }
}


void UnitSettingState::endStep() {

}


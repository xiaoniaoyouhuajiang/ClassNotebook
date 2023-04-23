#include "Base.hpp"

#include <algorithm>

#include "Units/Unit.hpp"
#include "Field/Field.hpp"
#include "Terrains/GroundTerrain.hpp"

Base::Base(int player, Field &field, FieldPosition basePosition) {
    m_player = player;
    field.getCell(basePosition)->setTerrain(std::make_shared<GroundTerrain>());
    field.getCell(basePosition)->setThing(nullptr);
    field.getCell({basePosition.row + 1, basePosition.col})->setTerrain(std::make_shared<GroundTerrain>());
    field.getCell({basePosition.row + 1, basePosition.col})->setThing(nullptr);
}

void Base::setCreationAbility(int creationAbility) {
    m_creationAbility = std::max(creationAbility, 0);
}

bool Base::hasSpaceToCreate(Field &field, FieldPosition basePosition) const {
    auto spaceCell = field.getCell({basePosition.row + 1, basePosition.col});
    return spaceCell->canHoldSomething();
}

FieldPosition Base::createUnit(const std::shared_ptr<const UnitFactory> &unitFactory, FieldPosition basePosition, Field &field) {
    if (m_creationAbility >= 2 && hasSpaceToCreate(field, basePosition)) {
        FieldPosition unitPosition = {basePosition.row + 1, basePosition.col};
        field.createUnit(unitFactory, unitPosition);
        field.getCell(unitPosition)->getUnit()->setBase(field.getCell(basePosition)->getBase());
        m_notifiers.insert(field.getCell(unitPosition)->getUnit().get());
        m_creationAbility -= 2;
        return unitPosition;
    }
    return {-1, -1};
}

void Base::reactOnUnitDeletion(const Unit *notifier) {
    if (m_notifiers.find(notifier) != m_notifiers.end()) {
        m_notifiers.erase(notifier);
        m_creationAbility += 1;
    }
}

void Base::modifyHealth(int change) {
    m_health = std::clamp(m_health + change, 0, getMaxHealth());
}

void Base::setHealth(int health) {
    m_health = std::clamp(health, 0, getMaxHealth());
}

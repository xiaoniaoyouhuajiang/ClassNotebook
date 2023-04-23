#include "UnitBaseHandler.h"
#include "Unit/IUnit.h"
#include "Base/Base.h"


void UnitBaseHandler::handle(IUnit* unit, Base* base) {
    if (unit->getPlayer() != base->getPlayer()) {
        UnitBaseAttackHandler attackHandler;
        attackHandler.handle(unit, base);
    }
}

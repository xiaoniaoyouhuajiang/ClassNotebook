#include "UnitUnitHandler.h"
#include "Unit/UnitHeader.h"


void UnitUnitHandler::handle(IUnit* active, IUnit* passive) {
    if (active->getPlayer() != passive->getPlayer()) {
        UnitUnitAttackHandler attackHandler;
        attackHandler.handle(active, passive);
    }
    else {
        UnitUnitUnionHandler unionHandler;
        unionHandler.handle(active, passive);
    }
}

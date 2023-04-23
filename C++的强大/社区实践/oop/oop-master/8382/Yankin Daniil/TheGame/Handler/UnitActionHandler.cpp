#include "UnitActionHandler.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"
#include "Landscape/LandscapeHeader.h"


void UnitActionHandler::handle(IUnit* unit, Object* passive) {
    if (passive->getGroupType() == UNIT) {
        UnitUnitHandler unitHandler;
        unitHandler.handle(unit, static_cast<IUnit*>(passive));
    }
    else if (passive->getGroupType() == BASE) {
        UnitBaseHandler baseHandler;
        baseHandler.handle(unit, static_cast<Base*>(passive));
    }
    else if (passive->getGroupType() == LAND) {
        UnitLandscapeHandler landHandler;
        landHandler.handle(unit, static_cast<ILandscape*>(passive));
    }
}

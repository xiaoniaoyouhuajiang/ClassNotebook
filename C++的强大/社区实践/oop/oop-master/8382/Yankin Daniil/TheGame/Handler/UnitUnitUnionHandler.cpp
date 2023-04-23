#include "UnitUnitUnionHandler.h"
#include "Player/Player.h"
#include "Unit/UnitHeader.h"
#include "Handler/RouteHandler.h"


void UnitUnitUnionHandler::handle(IUnit* active, IUnit* passive) {
    std::vector<int> logParameters = {active->getObjectType(), active->getPoint().getX(), active->getPoint().getY(), active->getPlayer()->getColor(),
                                     passive->getObjectType(), passive->getPoint().getX(), passive->getPoint().getY(), passive->getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_USER_UNITE, logParameters);

    RouteHandler routeHandler;
    bool success = routeHandler.handle(active, passive->getPoint(), false);
    if (!success)
        return;
    active->unite(passive);
}

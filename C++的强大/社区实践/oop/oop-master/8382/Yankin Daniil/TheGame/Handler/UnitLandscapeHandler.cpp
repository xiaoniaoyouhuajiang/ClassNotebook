#include "UnitLandscapeHandler.h"
#include "Landscape/ILandscape.h"
#include "Player/Player.h"
#include "Unit/UnitHeader.h"
#include "RouteHandler.h"


void UnitLandscapeHandler::handle(IUnit* unit, ILandscape* land) {
    std::vector<int> logParameters = {unit->getObjectType(), unit->getPoint().getX(), unit->getPoint().getY(), unit->getPlayer()->getColor(),
                                     land->getPoint().getX(), land->getPoint().getY()};
    Game::getInstance().getLogAdapter().log(LOG_USER_MOVE, logParameters);

    RouteHandler routeHandler;
    routeHandler.handle(unit, land->getPoint(), true);
}

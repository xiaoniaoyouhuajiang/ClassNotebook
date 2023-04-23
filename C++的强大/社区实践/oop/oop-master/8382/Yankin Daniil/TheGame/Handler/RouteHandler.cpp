#include "RouteHandler.h"
#include "Trivia/Point.h"
#include "Unit/UnitHeader.h"
#include "Command/Command.h"


bool RouteHandler::handle(IUnit* unit, Point point, bool toTheEnd) {
    std::vector <Point> route;
    Game::getInstance().getGameFacade().getRoute(unit->getPoint(), point, route);
    if (route.empty())
        return false;

    if (!toTheEnd)
        route.erase(route.begin());

    UnitMoveCommand moveCommand(unit, &route);
    bool success = moveCommand.execute();

    return success;
}

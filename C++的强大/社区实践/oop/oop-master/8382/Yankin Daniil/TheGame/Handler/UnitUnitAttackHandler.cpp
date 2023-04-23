#include "UnitUnitAttackHandler.h"
#include "Player/Player.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"
#include "Handler/RouteHandler.h"


void UnitUnitAttackHandler::handle(IUnit* attacker, IUnit* defender) {
    std::vector<int> logParameters = {attacker->getObjectType(), attacker->getPoint().getX(), attacker->getPoint().getY(), attacker->getPlayer()->getColor(),
                                     defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_USER_ATTACK, logParameters);

    if (attacker->getAttackRadius() == 0) {
        RouteHandler routeHandler;
        bool success = routeHandler.handle(attacker, defender->getPoint(), false);
        if (!success)
            return;
    }
    attacker->attack(defender);
}

#include "UnitBaseAttackHandler.h"
#include "Player/Player.h"
#include "Unit/IUnit.h"
#include "Base/Base.h"
#include "RouteHandler.h"


void UnitBaseAttackHandler::handle(IUnit* attacker, Base* base) {
    std::vector<int> logParameters = {attacker->getObjectType(), attacker->getPoint().getX(), attacker->getPoint().getY(), attacker->getPlayer()->getColor(),
                                     base->getObjectType(), base->getPoint().getX(), base->getPoint().getY(), base->getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_USER_ATTACK, logParameters);

    if (attacker->getAttackRadius() == 0) {
        RouteHandler routeHandler;
        bool success = routeHandler.handle(attacker, base->getPoint(), false);
        if (!success)
            return;
    }
    attacker->attack(base);
}

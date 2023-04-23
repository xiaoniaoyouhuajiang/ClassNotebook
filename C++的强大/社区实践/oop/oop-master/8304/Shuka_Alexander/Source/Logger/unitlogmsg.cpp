#include "unitlogmsg.h"

using namespace unit;


std::string UnitLogMsg::moveMessage(std::shared_ptr<Unit> unit,
                                    const Point2D& from, const Point2D& to)
{
    std::string result = "Unit: ";

    result += unit->draw();
    result += ". ";

    result += getPlayer(unit) + " ";
    result += "Move from (" + std::to_string(from.x) + ", " +
            std::to_string(from.y) + ") ";
    result += "Move to (" + std::to_string(to.x) + ", " +
            std::to_string(to.y) + ")";

    return result;
}


std::string UnitLogMsg::createMessage(std::shared_ptr<Unit> unit)
{
    std::string result = "Unit: ";

    result += unit->draw();
    result += ". ";

    result += getPlayer(unit) + " ";
    result += "Was create on position (" +  std::to_string(unit->getPosition().x) +
            ", " + std::to_string(unit->getPosition().y) + ")";

    return result;
}


std::string UnitLogMsg::dieMessage(std::shared_ptr<Unit> unit)
{
    std::string result = "Unit: ";

    result += unit->draw();
    result += ". ";

    result += getPlayer(unit) + " ";
    result += "Died on position (" +  std::to_string(unit->getPosition().x) + ", " +
            std::to_string(unit->getPosition().y) + ")";

    return result;
}


std::string UnitLogMsg::hurtMessage(std::shared_ptr<Unit> unit,
                                    double damage)
{
    std::string result = "Unit: ";

    result += unit->draw();
    result += ". ";

    result += getPlayer(unit) + " ";
    result += "Take damage: " +  std::to_string(damage);

    return result;
}


std::string UnitLogMsg::attackMessage(std::shared_ptr<Unit> unit,
                                      std::shared_ptr<Unit> enemy)
{
    std::string result = "Unit: ";

    result += unit->draw();
    result += ". ";

    result += getPlayer(unit) + " ";
    result += "Attack to enemy unit: ";
    result += enemy->draw();
    result += ". ";
    result += getPlayer(enemy) += " ";
    result += "Enemy position: (" +
            std::to_string(enemy->getPosition().x) + ", " +
            std::to_string(enemy->getPosition().y) + ")";

    return result;
}


std::string UnitLogMsg::getPlayer(std::shared_ptr<Unit> unit)
{
    if (unit->getPlayer() == PLAYER::ONE) {
        return "Player: 1.";
    }

    return "Player: 2.";
}

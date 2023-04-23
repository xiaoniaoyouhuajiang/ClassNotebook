#include "unitlog.hpp"

using namespace unit;


std::string UnitLog::moveMessage(std::shared_ptr<unit::Unit> unit,
                                    const Position2D& from, const Position2D& to)
{
    std::string result = "Unit: ";

    result += unit->getUnitName()[0];
    result += ". ";

    result += getPlayer(unit) + " ";
    result += "Move from (" + std::to_string(from.x) + ", " +
            std::to_string(from.y) + ") ";
    result += "Move to (" + std::to_string(to.x) + ", " +
            std::to_string(to.y) + ")";

    return result;
}


std::string UnitLog::createMessage(std::shared_ptr<unit::Unit> unit)
{
    std::string result = "Unit: ";

    result +=  unit->getUnitName()[0];
    result += ". ";

    result += getPlayer(unit) + " ";
    result += "Was created on position (" +  std::to_string(unit->getPosition().x) +
            ", " + std::to_string(unit->getPosition().y) + ")";

    return result;
}


std::string UnitLog::dieMessage(std::shared_ptr<unit::Unit> unit)
{
    std::string result = "Unit: ";

    result +=  unit->getUnitName()[0];
    result += ". ";

    result += getPlayer(unit) + " ";
    result += "Died on position (" +  std::to_string(unit->getPosition().x) + ", " +
            std::to_string(unit->getPosition().y) + ")";

    return result;
}


std::string UnitLog::healthMessage(std::shared_ptr<unit::Unit> unit,
                                    double damage)
{
    std::string result = "Unit: ";

    result += unit->getUnitName()[0];
    result += ". ";

    result += getPlayer(unit) + " ";
    result += "Take damage: " +  std::to_string(damage);

    return result;
}


std::string UnitLog::attackMessage(std::shared_ptr<unit::Unit> unit,
                                      std::shared_ptr<unit::Unit> enemy)
{
    std::string result = "Unit: ";

    result +=  unit->getUnitName()[0];
    result += ". ";

    result += getPlayer(unit) + " ";
    result += "Attack to enemy unit: ";
    result += enemy->getUnitName()[0];
    result += ". ";
    result += getPlayer(enemy) += " ";
    result += "Enemy position: (" +
            std::to_string(enemy->getPosition().x) + ", " +
            std::to_string(enemy->getPosition().y) + ")";

    return result;
}


std::string UnitLog::getPlayer(std::shared_ptr<unit::Unit> unit)
{
    if (unit->getPlayer() == PLAYER::ONE) {
        return "Player: 1.";
    }

    return "Player: 2.";
}

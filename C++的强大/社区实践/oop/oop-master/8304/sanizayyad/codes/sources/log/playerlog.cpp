#include "playerlog.hpp"

using namespace unit;

std::string PlayerLog::createUnit(bool isCreate, unit::PLAYER player)
{
    std::string result = getPlayer(player);
    if (!isCreate) {
        result += "Unit wasn't create!";
        return result;
    }

    result += "Unit was create";

    return result;
}


std::string PlayerLog::attack(unit::PLAYER player)
{
    std::string result = getPlayer(player);
    result += "Now is attacking.";
    return result;
}


std::string PlayerLog::deffend(unit::PLAYER player)
{
    std::string result = getPlayer(player);
    result += "Now is deffending.";
    return result;
}


std::string PlayerLog::getPlayer(unit::PLAYER player)
{
    if (player == PLAYER::ONE) {
        return "Player: 1. ";
    }

    return "Player: 2. ";
}

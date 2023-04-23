#include "playerlogmsg.h"

using namespace unit;


std::string PlayerLogMsg::createUnit(bool isCreate, PLAYER player)
{
    std::string result = getPlayer(player);
    if (!isCreate) {
        result += "Unit wasn't create!";
        return result;
    }

    result += "Unit was create";

    return result;
}


std::string PlayerLogMsg::attack(PLAYER player)
{
    std::string result = getPlayer(player);
    result += "Now is attacking.";
    return result;
}


std::string PlayerLogMsg::deffend(PLAYER player)
{
    std::string result = getPlayer(player);
    result += "Now is deffending.";
    return result;
}


std::string PlayerLogMsg::getPlayer(PLAYER player)
{
    if (player == PLAYER::ONE) {
        return "Player: 1. ";
    }

    return "Player: 2. ";
}

#ifndef PLAYERLOGMSG_H
#define PLAYERLOGMSG_H

#include <string>

#include "Unit/unit.h"


class PlayerLogMsg
{
public:
    static std::string createUnit(bool isCreate, unit::PLAYER player);
    static std::string attack(unit::PLAYER player);
    static std::string deffend(unit::PLAYER player);

private:
    static std::string getPlayer(unit::PLAYER player);
};

#endif // PLAYERLOGMSG_H

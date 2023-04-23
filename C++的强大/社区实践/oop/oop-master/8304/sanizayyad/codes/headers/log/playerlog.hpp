#ifndef playerlog_hpp
#define playerlog_hpp

#include "unit.hpp"

#include <stdio.h>


class PlayerLog
{
public:
    static std::string createUnit(bool isCreate, unit::PLAYER player);
    static std::string attack(unit::PLAYER player);
    static std::string deffend(unit::PLAYER player);

private:
    static std::string getPlayer(unit::PLAYER player);
};


#endif /* playerlog_hpp */

#ifndef UNITLOGMSG_H
#define UNITLOGMSG_H

#include "Unit/unit.h"


class UnitLogMsg
{
public:
    static std::string moveMessage(std::shared_ptr<unit::Unit> unit,
                                   const Point2D& from, const Point2D& to);

    static std::string createMessage(std::shared_ptr<unit::Unit> unit);

    static std::string dieMessage(std::shared_ptr<unit::Unit> unit);

    static std::string hurtMessage(std::shared_ptr<unit::Unit> unit, double damage);

    static std::string attackMessage(std::shared_ptr<unit::Unit> unit,
                                     std::shared_ptr<unit::Unit> enemy);

private:
    static std::string getPlayer(std::shared_ptr<unit::Unit> unit);
};

#endif // UNITLOGMSG_H

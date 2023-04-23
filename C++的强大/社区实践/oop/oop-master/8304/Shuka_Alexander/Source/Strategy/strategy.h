#ifndef STRATEGY_H
#define STRATEGY_H

#include <qglobal.h>

#include "Unit/unit.h"


class Strategy
{
public:
    virtual ~Strategy() = default;

    virtual void changeUnit(std::shared_ptr<unit::Unit> unit) const = 0;

    virtual std::shared_ptr<Strategy> clone() const = 0;
};

#endif // STRATEGY_H

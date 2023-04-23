#ifndef KILLSTRATEGY_H
#define KILLSTRATEGY_H

#include "Strategy/strategy.h"


class KillStrategy : public Strategy
{
public:
    virtual void changeUnit(std::shared_ptr<unit::Unit> unit) const override;

    virtual std::shared_ptr<Strategy> clone() const override;
};

#endif // KILLSTRATEGY_H

#ifndef NOSTRATEGY_H
#define NOSTRATEGY_H

#include "Strategy/strategy.h"


class NoStrategy : public Strategy
{
public:
    virtual void changeUnit(std::shared_ptr<unit::Unit> unit) const override;

    virtual std::shared_ptr<Strategy> clone() const override;
};

#endif // NOSTRATEGY_H

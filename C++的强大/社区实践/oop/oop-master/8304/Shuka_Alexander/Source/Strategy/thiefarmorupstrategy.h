#ifndef THIEFARMORUPSTRATEGY_H
#define THIEFARMORUPSTRATEGY_H

#include "strategy.h"

#include "Factory/ArmorFactory/lightarmorfactory.h"


class ThiefArmorUpStrategy : public Strategy
{
public:
    virtual void changeUnit(std::shared_ptr<unit::Unit> unit) const override;

    virtual std::shared_ptr<Strategy> clone() const override;
};

#endif // THIEFARMORUPSTRATEGY_H

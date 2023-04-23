#ifndef KAMIKADZEARMORUPSTRATEGY_H
#define KAMIKADZEARMORUPSTRATEGY_H

#include "strategy.h"

#include "Factory/ArmorFactory/lightarmorfactory.h"


class KamikadzeArmorUpStrategy : public Strategy
{
public:
    virtual void changeUnit(std::shared_ptr<unit::Unit> unit) const override;

    virtual std::shared_ptr<Strategy> clone() const override;
};

#endif // KAMIKADZEARMORUPSTRATEGY_H

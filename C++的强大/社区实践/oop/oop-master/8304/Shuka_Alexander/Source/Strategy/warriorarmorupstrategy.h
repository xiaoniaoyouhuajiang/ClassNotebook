#ifndef WARRIORARMORUPSTRATEGY_H
#define WARRIORARMORUPSTRATEGY_H

#include "strategy.h"

#include "Factory/ArmorFactory/mediumarmorfactory.h"


class WarriorArmorUpStrategy : public Strategy
{
public:
    virtual void changeUnit(std::shared_ptr<unit::Unit> unit) const override;

    virtual std::shared_ptr<Strategy> clone() const override;
};

#endif // WARRIORARMORUPSTRATEGY_H

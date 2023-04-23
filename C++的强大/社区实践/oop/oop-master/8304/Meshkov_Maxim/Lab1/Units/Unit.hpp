#pragma once

#include <string>
#include <memory>

class Unit {
public:
    virtual ~Unit() = default;

    virtual std::string getName() const = 0;

    virtual std::shared_ptr<Unit> createNewOfSameType() const = 0;
    virtual std::shared_ptr<Unit> createCopy() const = 0;

    virtual int getHealth() const = 0;
    // TODO UnitModifier for changing properties (temporary or constantly)

    virtual int getHit() const = 0;

    virtual bool icesWhenAttacks() const = 0;

    virtual int getArmor() const = 0;

    virtual int getMoveRange() const = 0;

    virtual int getAttackRange() const = 0;

    virtual bool isIced() const = 0;

protected:
    Unit &operator=(const Unit&) = default;
};
#pragma once

#include <string>
#include <memory>
#include <set>

#include "../Creature.hpp"
class UnitFactory;
class Field;
#include "../FieldPosition.hpp"
class Base;

class Unit : public Creature {
public:
    virtual ~Unit() = default;

    virtual std::shared_ptr<UnitFactory> createUnitFactory() const = 0;
    virtual std::shared_ptr<Unit> createCopy() const = 0;

    virtual int getHit() const = 0;
    virtual bool icesWhenAttacks() const = 0;
    virtual int getArmor() const = 0;
    virtual int getMoveRange() const = 0;
    virtual int getAttackRange() const = 0;
    virtual bool isIced() const = 0;
    virtual void ice() = 0;

    virtual std::set<FieldPosition> findPossibleMoves(FieldPosition unitPosition, const Field &field) const = 0;
    virtual std::set<FieldPosition> findPossibleAttacks(FieldPosition unitPosition, const Field &field) const = 0;

    virtual void attack(FieldPosition victimPosition, Field &field) = 0;

    virtual std::weak_ptr<const Base> getBase() const = 0;
    virtual void setBase(std::weak_ptr<Base>) = 0;
    virtual void notifyAboutDeletionFromField() = 0;

    virtual void setPlayer(std::optional<int> player) = 0;
    virtual void setIsIced(int isIced) = 0;

protected:
    Unit &operator=(const Unit&) = default;
};

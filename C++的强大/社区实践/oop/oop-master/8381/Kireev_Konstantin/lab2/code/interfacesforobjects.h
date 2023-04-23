#pragma once
#include "printInterface.h"
#include "feature.h"
#include "observerForCreatures.h"
#include "observerForBaseToUnits.h"

class NeutralObjectInterface;
class UnitInterface;
class NeutralObjectsEffectStrategyInterface;

enum Type { HUMAN, ELF };
enum CreatureType { BASE, UNIT };


class CreatureInterface : public printInterface, public CreatureObservableByFieldComponentInterface
{
protected:
    Feature* health;
    Type type;

public:
    virtual CreatureInterface* copy() = 0;
    virtual bool isMove() = 0;
    virtual CreatureType getCreatureType() const = 0;
    virtual void takeDamage(int damage) = 0;
    virtual void setHealth(int newHealth) = 0;

    void attachFieldComponent(CreatureObserverInterface* fieldComponent) override
    {
        this->fieldComponentAttachedTo = fieldComponent;
    }

    Type getRace() const
    {
        return this->type;
    }
    Feature getHealth() const
    {
        return *health;
    }
};



class NeutralObjectInterface : public printInterface
{
protected:
    NeutralObjectsEffectStrategyInterface* strategy;
public:
    virtual ~NeutralObjectInterface()
    {
        delete strategy;
    }
    virtual void unitInfl(UnitInterface* unit) = 0;
    virtual NeutralObjectInterface* copy() = 0;
};



enum UnitType { DMG_ABS_INF, DMG_ABS_CAV,
                DMG_ABS_ARC, CRT_DMG_INF,
                CRT_DMG_CAV, CRT_DMG_ARC };

class UnitInterface : public CreatureInterface, public UnitObservableByBaseInterface
{
protected:
    Feature* armor;
    Feature* damage;

public:
    virtual UnitType getType() const = 0;

    void attachBase(UnitObserverInterface* base) override
    {
        this->base = base;
    }

    bool isMove() override
    {
        return true;
    }

    CreatureType getCreatureType() const override
    {
        return UNIT;
    }

    void setHealth(int newHealth) override
    {
        health->setValue(newHealth);
        if(newHealth <= 0)
        {
            base->onUnitDestroyed(this);
            fieldComponentAttachedTo->onCreatureDestroyed();
        }
    }

    Feature* getArmor() const
    {
        return armor;
    }
    void setArmor(int newArmor)
    {
        *armor = newArmor;
    }

    Feature* getDamage() const
    {
        return damage;
    }
    void setDamage(int newDamage)
    {
        *damage = newDamage;
    }

    void setAllAttribues(int health, int armor, int damage)
    {
        this->health->setValue(health);
        this->armor->setValue(armor);
        this->damage->setValue(damage);
    }

    void commitAttack(CreatureInterface* attackedUnit)
    {
        int damage = this->damage->getValue() + this->damage->getExtra();
        attackedUnit->takeDamage(damage);
    }

    void clearNeutralObjectEffect()
    {
        health->setExtra(0);
        armor->setExtra(0);
        damage->setExtra(0);
    }

    UnitInterface& operator+=(NeutralObjectInterface* neutralObject)
    {
        neutralObject->unitInfl(this);
        return *this;
    }
};

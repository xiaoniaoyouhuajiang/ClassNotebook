#pragma once
#include "printInterface.h"
#include "feature.h"
#include "observerForCreatures.h"
#include "observerForBaseToUnits.h"

class UnitInterface;
class NeutralObjectInterface;
class NeutralObjectsEffectStrategyInterface;


enum CreatureType { BASE, UNIT };

class CreatureInterface : public printInterface, public CreatureObservableByFieldComponentInterface
{
protected:
    Feature* health;

    unsigned int possessorId;
public:
    virtual CreatureInterface* copy() = 0;
    virtual bool isMoveable() = 0;
    virtual CreatureType getCreatureType() const = 0;
    virtual void takeDamage(int damage) = 0;
    virtual void setHealth(int newHealth) = 0;

    void attachFieldComponent(CreatureObserverInterface* fieldComponent) override
    {
        this->fieldComponentAttachedTo = fieldComponent;
    }

    unsigned int getPossessorId() const
    {
        return this->possessorId;
    }

    Feature getHealth() const
    {
        return *health;
    }
};


enum NeutralObjectType { GUNSMITH, VILLAGE, ARMORHOUSE, BOOSTTOWER };

class NeutralObjectInterface : public printInterface
{
protected:
    NeutralObjectsEffectStrategyInterface* strategy;
public:
    virtual ~NeutralObjectInterface() { delete strategy; }
    virtual void influenceOnUnit(UnitInterface* unit) = 0;
    virtual NeutralObjectType getType() = 0;
    virtual NeutralObjectInterface* copy() = 0;
};





enum UnitType { ABSORB_INFANTRY, ABSORB_CAVALRY, ABSORB_ARCHER,
                CRIT_INFANTRY, CRIT_CAVALRY, CRIT_ARCHER };

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

    bool isMoveable() override
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

    void commitAttack(CreatureInterface* attackedCreature)
    {
        int damage = this->damage->getValue() + this->damage->getBonus();
        attackedCreature->takeDamage(damage);
    }

    void clearNeutralObjectEffect()
    {
        health->setBonus(0);
        armor->setBonus(0);
        damage->setBonus(0);
    }

    UnitInterface& operator+=(NeutralObjectInterface* neutralObject)
    {
        neutralObject->influenceOnUnit(this);
        return *this;
    }
};


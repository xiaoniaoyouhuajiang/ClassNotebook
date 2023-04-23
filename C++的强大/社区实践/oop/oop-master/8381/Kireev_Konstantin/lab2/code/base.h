#pragma once
#include "field.h"
#include "abstractFactory.h"
#include "observerForBaseToUnits.h"

class Base : public CreatureInterface, public UnitObserverInterface
{
private:
    Field* field;

    AbstractFactory* critDealersFactory = new CritUnitsFactory();
    AbstractFactory* absorbersFactory = new DamageAbsorberUnitsFactory();

public:
    Base(Field* field, Type type)
    {
        this->field = field;
        if (type == HUMAN)
            field->addObject(field->getNmRows()/2, 0, this);
        else if (type == ELF)
            field->addObject(field->getNmRows()/2, field->getNmColumns()-1, this);
        this->type = type;
        this->health = new Feature(200);
    }

    ~Base()
    {
        delete field;
        delete critDealersFactory;
        delete absorbersFactory;
    }

    QString getClass() override
    {
        return "  BASE";
    }

    bool isMove() override
    {
        return false;
    }

    CreatureType getCreatureType() const override
    {
        return BASE;
    }

    void onUnitDestroyed(UnitInterface* destroyedUnit) override
    {
        delete destroyedUnit;
    }

    CreatureInterface* copy() override
    {
        return new Base(*this);
    }

    void takeDamage(int damage) override
    {
        int healthValue = health->getValue();
        this->setHealth(healthValue - damage);
    }

    Feature getHealth() const
    {
        return *health;
    }

    void setHealth(int newHealth) override
    {
        health->setValue(newHealth);
        if(newHealth <= 0)
            fieldComponentAttachedTo->onCreatureDestroyed();
    }

    void createUnit(UnitType unitType, unsigned int row, unsigned int column)
    {
        try
        {
            UnitInterface* unit;
            switch (unitType)
            {
                case CRT_DMG_INF:
                    unit = critDealersFactory->createInfantry(type);
                    break;
                case CRT_DMG_CAV:
                    unit = critDealersFactory->createCavalry(type);
                    break;
                case CRT_DMG_ARC:
                    unit = critDealersFactory->createArcher(type);
                    break;
                case DMG_ABS_INF:
                    unit = absorbersFactory->createInfantry(type);
                    break;
                case DMG_ABS_CAV:
                    unit = absorbersFactory->createCavalry(type);
                    break;
                case DMG_ABS_ARC:
                    unit = absorbersFactory->createArcher(type);
                    break;
            }
            unit->attachBase(this);
            field->addObject(row, column, unit);
        }
        catch (...)
        {
        }
    }
};

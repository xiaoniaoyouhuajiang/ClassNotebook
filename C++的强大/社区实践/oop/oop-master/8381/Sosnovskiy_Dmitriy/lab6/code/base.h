#pragma once
#include <vector>

#include "field.h"
#include "abstractfactory.h"
#include "base_unit_observer_interfaces.h"

#include <snapshot.h>

class Base : public ICreature, public IUnitObserver
{
private:
    Field* field;

    AbstractUnitFactory* critDealersFactory = new CritDealersFactory();

    AbstractUnitFactory* absorbersFactory = new AbsorbersFactory();

    std::vector<IUnit*> units;

public:    
    Base(Field* field, unsigned int rowNumber, unsigned int columnNumber, unsigned int possessorId) {
        this->field = field;
        field->placeCreature(rowNumber, columnNumber, this);
        this->possessorId = possessorId;
        this->health = new Attribute(100);
    }

    ~Base()
    {
        delete field;
        delete critDealersFactory;
        delete absorbersFactory;
    }

    QString getClass() override { return "Base"; }

    bool isMoveable() override { return false; }

    CreatureType getCreatureType() const override { return BASE; }

    void onUnitDestroyed(IUnit* destroyedUnit) override
    {
        for(unsigned int i = 0; i < units.size(); i++)
        {
            if(units[i] == destroyedUnit)
            {
                units.erase(units.begin() + i);
                break;
            }
        }

        delete destroyedUnit;

        field->onUnitDestroyed();
    }

    ICreature* copy() override { return new Base(*this); }

    void takeDamage(int damage) override {
        int healthValue = health->getValue();
        this->setHealth(healthValue - damage);
    }

    Attribute getHealth() const { return *health; }

    void setHealth(int newHealth) override {
        health->setValue(newHealth);
        if(newHealth <= 0) {
            fieldComponentAttachedTo->onCreatureDestroyed();
            for(auto unit : units) unit->setHealth(-1);
        }
    }

    bool isDemolished() {
        return health->getValue() <=0 ? true: false;
    }

    QString getInfo(){
        QString returnable = nullptr;

        returnable.append("Base of player number " + QString::number(possessorId) + "\n" +
                          "Health of the base = " + QString::number(health->getValue()) + "\n" +
                          "Units attached to the base:\n");

        returnable.append(units.size() == 0 ? "No units" : "");

        for(int i = 0; i < units.size(); i++)
        {
            returnable.append(units[i]->getClass() + " health:" + QString::number(units[i]->getHealth().getValue()) + "\n");
        }

        return  returnable;
    }

    void createUnit(UnitType unitType, unsigned int row, unsigned int column) {
        IUnit* unit;
        switch (unitType) {
            case CRIT_INFANTRY:
                unit = critDealersFactory->createInfantry(this->possessorId);
                break;
            case CRIT_CAVALRY:
                unit = critDealersFactory->createCavalry(this->possessorId);
                break;
            case CRIT_ARCHER:
                unit = critDealersFactory->createArcher(this->possessorId);
                break;
            case ABSORB_INFANTRY:
                unit = absorbersFactory->createInfantry(this->possessorId);
                break;
            case ABSORB_CAVALRY:
                unit = absorbersFactory->createCavalry(this->possessorId);
                break;
            case ABSORB_ARCHER:
                unit = absorbersFactory->createArcher(this->possessorId);
                break;
        }

        field->placeCreature(row, column, unit);

        unit->attachBase(this);

        units.push_back(unit);
    }


    BaseSnapshot* createSnapshot()
    {
        BaseSnapshot* snapshot = new BaseSnapshot(health->getValue(), possessorId, coordinates);
        return snapshot;
    }
};


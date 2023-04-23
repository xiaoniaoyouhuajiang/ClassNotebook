#pragma once
#include "iprintable.h"
#include "landscapes.h"
#include "creatures_basic_interfaces.h"
#include "fieldcomponent_creature_observer_interfaces.h"
#include "neutral_objects.h"


class FieldComponent : public ICreatureObserver
{
private:
    ILandscape* landscapeProxy;
    ICreature* creature;
    INeutralObject* object;
public:
    FieldComponent(ILandscape* landscape = new Ground(), ICreature* creature = nullptr, INeutralObject* object = nullptr) :
        creature(creature), object(object) { landscapeProxy = new LandscapeProxy(landscape); }
    ~FieldComponent(){
        delete landscapeProxy;
        delete creature;
        delete object;
    }

    FieldComponent* copy()
    {
        FieldComponent* sameFieldComponent = new FieldComponent();
        sameFieldComponent->landscapeProxy = landscapeProxy->copy();
        sameFieldComponent->creature = creature->copy();
        sameFieldComponent->object = object->copy();

        return sameFieldComponent;
    }

    QString getLandscapeInfo(){
        return landscapeProxy->getClass();
    }

    QString getCreatureInfo(){
        if(hasCreature()) return creature->getClass();
        else return "no_creature";
    }

    QString getObjectInfo()
    {
        if(hasNeutralObject()) return object->getClass();
        else return "no_object";
    }

    bool hasCreature() const { return (creature == nullptr) ? false : true; }

    bool hasNeutralObject() const { return (object == nullptr) ? false : true; }

    bool canHoldCreature() const { return landscapeProxy->canHoldCreature(); }

    void onCreatureDestroyed()
    {
        creature = nullptr;
    }

    ILandscape* getLandscape() const { return landscapeProxy; }
    void setLandscape(ILandscape* landscape) { this->landscapeProxy = new LandscapeProxy(landscape); }

    ICreature* getCreature() const { return creature; }
    void setCreature(ICreature* newCreature) {

        if(newCreature == nullptr)
        {
            this->creature = nullptr;
            return;
        }

        if(newCreature->getCreatureType() == UNIT)
        {
            IUnit* unit = dynamic_cast<IUnit*>(newCreature);

            if(this->hasNeutralObject()) *unit += object;
        }

        this->creature = newCreature;

        newCreature->attachFieldComponent(this);
    }

    INeutralObject* getNeutralObject() const { return object; }
    void setNeutralObject(INeutralObject* object) { this->object = object; }
};

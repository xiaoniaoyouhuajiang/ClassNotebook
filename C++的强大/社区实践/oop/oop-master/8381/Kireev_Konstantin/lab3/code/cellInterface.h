#pragma once
#include "printInterface.h"
#include "landscapes.h"
#include "interfacesforobjects.h"
#include "observerForCreatures.h"
#include "neutralObjects.h"


class cellInterface : public CreatureObserverInterface
{
private:
    LandscapeInterface* landscapeProxy;
    CreatureInterface* creature;
    NeutralObjectInterface* object;
public:
    cellInterface(LandscapeInterface* landscape = new Ground(), CreatureInterface* creature = nullptr, NeutralObjectInterface* object = nullptr) :
        creature(creature), object(object) { landscapeProxy = new LandscapeProxy(landscape); }
    ~cellInterface(){
        delete landscapeProxy;
        delete creature;
        delete object;
    }

    cellInterface* copy()
    {
        cellInterface* sameFieldComponent = new cellInterface();
        sameFieldComponent->landscapeProxy = landscapeProxy->copy();
        sameFieldComponent->creature = creature->copy();
        sameFieldComponent->object = object->copy();

        return sameFieldComponent;
    }

    QString getLandscapeInfo()
    {
        return landscapeProxy->getClass();
    }

    QString getCreatureInfo()
    {
        if(hasCreature())
            return creature->getClass();
        else
            return "no creature";
    }

    QString getObjectInfo()
    {
        if(hasNeutralObject())
            return object->getClass();
        else
            return "no object";
    }

    bool hasCreature() const
    {
        return (creature == nullptr) ? false : true;
    }

    bool hasNeutralObject() const
    {
        return (object == nullptr) ? false : true;
    }

    bool canHoldCreature() const
    {
        return landscapeProxy->canHoldCreature();
    }

    void onCreatureDestroyed()
    {
        creature = nullptr;
    }

    LandscapeInterface* getLandscape() const
    {
        return landscapeProxy;
    }
    void setLandscape(LandscapeInterface* landscape)
    {
        this->landscapeProxy = new LandscapeProxy(landscape);
    }

    CreatureInterface* getCreature() const
    {
        return creature;
    }
    void setCreature(CreatureInterface* newCreature)
    {

        if (newCreature == nullptr)
        {
            this->creature = nullptr;
            return;
        }

        if (newCreature->getCreatureType() == UNIT)
        {
            UnitInterface* unit = dynamic_cast<UnitInterface*>(newCreature);

            if (this->hasNeutralObject()) *unit += object;
        }

        this->creature = newCreature;

        newCreature->attachFieldComponent(this);
    }

    NeutralObjectInterface* getNeutralObject() const
    {
        return object;
    }
    void setNeutralObject(NeutralObjectInterface* object)
    {
        this->object = object;
    }
};

#ifndef CELLINTERFACE_H
#define CELLINTERFACE_H
#include <printInterface.h>
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
    cellInterface(LandscapeInterface* landscape = new Ground()
                , CreatureInterface* creature = nullptr
                , NeutralObjectInterface* object = nullptr)
        : creature(creature)
        , object(object)
    {
        landscapeProxy = new Proxy(landscape);
    }

    ~cellInterface()
    {
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


    bool hasCreature() const
    {
        return (creature == nullptr) ? false : true;
    }

    QString getCreatureInfo()
    {
        if(hasCreature())
            return creature->getClass();
        else
            return "  space";
    }


    bool hasNeutralObject() const
    {
        return (object == nullptr) ? false : true;
    }

    QString getObjectInfo()
    {
        if(hasNeutralObject())
            return object->getClass();
        else
            return "  space";
    }


    bool canHoldCreature() const
    {
        return landscapeProxy->interaction();
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
        this->landscapeProxy = landscape;
    }

    NeutralObjectInterface* getNeutralObject() const
    {
        return object;
    }
    void setNeutralObject(NeutralObjectInterface* object)
    {
        this->object = object;
    }

    CreatureInterface* getCreature() const
    {
        return creature;
    }
    void setCreature(CreatureInterface* newCreature)
    {

        if (newCreature->getCreatureType() == UNIT)
        {
            UnitInterface* unit = dynamic_cast<UnitInterface*>(newCreature);

            if (this->hasNeutralObject())
                *unit += object;
        }

        this->creature = newCreature;
        newCreature->attachFieldComponent(this);
    }
};

#endif // CELLINTERFACE_H

#pragma once

class CreatureInterface;

class CreatureObserverInterface{
public:
    virtual ~CreatureObserverInterface() = default;
    virtual void onCreatureDestroyed() = 0;
};


class CreatureObservableByFieldComponentInterface
{
protected:
    CreatureObserverInterface* fieldComponentAttachedTo;
public:
    virtual ~CreatureObservableByFieldComponentInterface() = default;
    virtual void attachFieldComponent(CreatureObserverInterface* fieldComponent) = 0;
};

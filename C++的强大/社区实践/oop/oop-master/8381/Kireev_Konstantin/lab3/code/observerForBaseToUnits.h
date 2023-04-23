#ifndef OBSERVERFORBASETOUNITS_H
#define OBSERVERFORBASETOUNITS_H

#pragma once

class UnitInterface;

class UnitObserverInterface{
public:
    virtual ~UnitObserverInterface() = default;
    virtual void onUnitDestroyed(UnitInterface* destroyedUnit) = 0;
};


class UnitObservableByBaseInterface{
protected:
    UnitObserverInterface* base;
public:
    virtual ~UnitObservableByBaseInterface() = default;
    virtual void attachBase(UnitObserverInterface* base) = 0;
};


#endif // OBSERVERFORBASETOUNITS_H

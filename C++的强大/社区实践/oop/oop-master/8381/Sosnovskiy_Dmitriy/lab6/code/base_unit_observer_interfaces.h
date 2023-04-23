#pragma once

//Паттерн "наблюдатель" для базы и юнитов

class IUnit;

class IUnitObserver{
public:
    virtual ~IUnitObserver() = default;
    virtual void onUnitDestroyed(IUnit* destroyedUnit) = 0;
};


class IUnitObservableByBase{
protected:
    IUnitObserver* base;
public:
    virtual ~IUnitObservableByBase() = default;
    virtual void attachBase(IUnitObserver* base) = 0;
};

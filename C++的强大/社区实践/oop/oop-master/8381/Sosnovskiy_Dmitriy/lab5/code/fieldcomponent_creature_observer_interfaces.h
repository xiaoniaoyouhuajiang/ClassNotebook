#pragma once

//Дополнительный паттерн (В доп. баллы) "Наблюдатель" для клетки поля и существ, которые находятся в клетке поля (creature)

class ICreature;

class ICreatureObserver{
public:
    virtual ~ICreatureObserver() = default;
    virtual void onCreatureDestroyed() = 0;
};


class ICreatureObservableByFieldComponent
{
protected:
    ICreatureObserver* fieldComponentAttachedTo;
public:
    virtual ~ICreatureObservableByFieldComponent() = default;
    virtual void attachFieldComponent(ICreatureObserver* fieldComponent) = 0;
};

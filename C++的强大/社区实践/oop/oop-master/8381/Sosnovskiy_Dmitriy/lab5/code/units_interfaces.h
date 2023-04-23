#pragma once
#include "creatures_basic_interfaces.h"

class IInfantry : public virtual IUnit
{

};


class ICavalry : public virtual IUnit
{

};


class IArcher : public virtual IUnit
{

};


class ICritDealer : public virtual IUnit
{
protected:
    double critFactor;
public:
    void takeDamage(int damage) override {
        int healthValue = health->getValue();
        healthValue = (healthValue - (damage * critFactor - armor->getValue()));
        this->setHealth(healthValue);
    }
};


class IDamageAbsorber : public virtual IUnit
{
protected:
    double absorbtionCoefficient;
public:
    void takeDamage(int damage) override {
        int healthValue = health->getValue();
        healthValue = (healthValue - (damage - armor->getValue())) * (1 - absorbtionCoefficient);

        this->setHealth(healthValue);
    }
};

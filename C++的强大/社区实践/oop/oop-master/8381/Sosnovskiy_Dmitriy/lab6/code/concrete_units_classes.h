#pragma once
#include <units_interfaces.h>

class AbsorbInfantry : public IDamageAbsorber, public IInfantry
{
public:
    AbsorbInfantry(unsigned int possessorId);
    QString getClass() override;
    ICreature* copy() override { return new AbsorbInfantry(*this); }
    UnitType getType() const override { return ABSORB_INFANTRY; }
};


class CritInfantry : public IInfantry, public ICritDealer
{
public:
    CritInfantry(unsigned int possessorId);
    QString getClass() override;
    ICreature* copy() override { return new CritInfantry(*this); }
    UnitType getType() const override { return CRIT_INFANTRY; }

};


class AbsorbCavalry : public ICavalry, public IDamageAbsorber
{
public:
    AbsorbCavalry(unsigned int possessorId);
    QString getClass() override;
    ICreature* copy() override { return new AbsorbCavalry(*this); }
    UnitType getType() const override { return ABSORB_CAVALRY; }
};


class CritCavalry : public ICavalry, public ICritDealer
{
public:
    CritCavalry(unsigned int possessorId);
    QString getClass() override;
    ICreature* copy() override { return new CritCavalry(*this); }
    UnitType getType() const override { return CRIT_CAVALRY; }
};


class AbsorbArcher : public IArcher, public IDamageAbsorber
{
public:
    AbsorbArcher(unsigned int possessorId);
    QString getClass() override;
    ICreature* copy() override { return new AbsorbArcher(*this); }
    UnitType getType() const override { return ABSORB_ARCHER; }
};

class CritArcher : public IArcher, public ICritDealer
{
public:
    CritArcher(unsigned int possessorId);
    QString getClass() override;
    ICreature* copy() override { return new CritArcher(*this); }
    UnitType getType() const override { return CRIT_ARCHER; }
};

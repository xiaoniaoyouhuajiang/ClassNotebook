#include "unitsclasses.h"

DamageAbsorberInfantry::DamageAbsorberInfantry(Type type)
{
    health = new Feature(100);
    armor = new Feature(4);
    damage = new Feature(20);
    this->type = type;
    absorptionFactor = 0.3;
}

QString DamageAbsorberInfantry::getClass()
{
    return QString("DmgAbsInf");
}


CritInfantry::CritInfantry(Type type)
{
    health = new Feature(80);
    armor = new Feature(2);
    damage = new Feature(30);
    this->type = type;
    critFactor = 1.5;
}

QString CritInfantry::getClass()
{
    return QString("CrtDmgInf");
}


DamageAbsorberCavalry::DamageAbsorberCavalry(Type type)
{
    health = new Feature(150);
    armor = new Feature(8);
    damage = new Feature(25);
    this->type = type;
    absorptionFactor = 0.2;
}

QString DamageAbsorberCavalry::getClass()
{
    return QString("DmgAbsCav");
}


CritCavalry::CritCavalry(Type type)
{
    health = new Feature(120);
    armor = new Feature(3);
    damage = new Feature(40);
    this->type = type;
    critFactor = 1.25;
}

QString CritCavalry::getClass()
{
    return QString("CrtDmgCav");
}


DamageAbsorberArcher::DamageAbsorberArcher(Type type)
{
    health = new Feature(80);
    armor = new Feature(2);
    damage = new Feature(20);
    this->type = type;
    absorptionFactor = 0.1;
}

QString DamageAbsorberArcher::getClass()
{
    return QString("DmgAbsArc");
}


CritArcher::CritArcher(Type type)
{
    health = new Feature(60);
    armor = new Feature(2);
    damage = new Feature(40);
    this->type = type;
    critFactor = 1.75;
}

QString CritArcher::getClass()
{
    return QString("CrtDmgArc");
}


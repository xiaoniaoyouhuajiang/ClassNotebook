#pragma once
#include "IUnit.h"
#include "Infantary.h"
#include "Mechanisms.h"
#include "Shooters.h"

class Archer;
class Crossbowman;
class Ballista;
class Catapult;
class Spearman;
class Swordsman;

class UnitFañtory
{
private:
	static int id;
public:
	UnitFañtory() = default;
	static IUnit* createUnit(Units unitType);
};

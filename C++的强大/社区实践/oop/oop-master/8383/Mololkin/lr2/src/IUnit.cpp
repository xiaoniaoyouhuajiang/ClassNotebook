#include "IUnit.h"
#include "NeutralObjects.h"


IUnit& operator+=(IUnit& left, const Hospital& right)
{
	left.upHP(right.HPToAdd);
	return left;
}

IUnit& operator+=(IUnit& left, const AttackUpgrader& right)
{
	left.upAttack(right.attackToAdd);
	return left;
}

IUnit& operator+=(IUnit& left, const ArmourUpgrader& right)
{
	left.upArmour(right.armourToAdd);
	return left;
}

IUnit& operator+=(IUnit& left, const Spikes& right)
{
	left.downHP(right.damage);
	return left;
}

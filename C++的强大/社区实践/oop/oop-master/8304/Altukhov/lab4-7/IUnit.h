#pragma once
class Unit;
class IUnit {


public:

	virtual bool doAttack(Unit*& target) = 0;
	virtual void doMove(int x, int y) = 0;
	virtual bool tryToDie(Unit*& unit) = 0;
	//virtual void doSpecAbility() = 0;
	virtual ~IUnit() = default;

};

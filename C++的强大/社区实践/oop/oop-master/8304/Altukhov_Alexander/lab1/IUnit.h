#pragma once
class IUnit {


public:

	virtual void doAttack() = 0;
	virtual void doMove(int x, int y) = 0;
	//virtual void doSpecAbility() = 0;
	virtual ~IUnit() = default;

};

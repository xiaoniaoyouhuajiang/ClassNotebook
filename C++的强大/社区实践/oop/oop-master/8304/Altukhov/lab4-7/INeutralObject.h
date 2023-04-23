#pragma once
class Unit;

class INeutralObject {

public:


	virtual void applyEffect(Unit*& unit) = 0;
	virtual void removeEffect(Unit*& unit) = 0;

	virtual ~INeutralObject() = default;

};

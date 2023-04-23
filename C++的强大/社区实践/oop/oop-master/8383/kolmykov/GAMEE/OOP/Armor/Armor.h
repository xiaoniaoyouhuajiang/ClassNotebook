#pragma once
class Armor
{
protected:
	int defend;
public:
	Armor();
	Armor(const Armor& other);
	virtual ~Armor();
	int getDefend();
	
};
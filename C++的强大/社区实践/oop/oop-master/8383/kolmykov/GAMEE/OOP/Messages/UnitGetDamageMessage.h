#pragma once
#include "Message.h"
class UnitGetDamageMessage :
	public Message
{
private:
	int x;
	int y;
	int damage;
public:
	UnitGetDamageMessage();
	UnitGetDamageMessage(int x, int y, int damage);
	~UnitGetDamageMessage();
	std::string toString();
};


#pragma once
#include "Message.h"
class UnitAttackMessage :
	public Message
{
private:
	int x;
	int y;
public:
	UnitAttackMessage();
	UnitAttackMessage(int x, int y);
	~UnitAttackMessage();
	std::string toString();
};


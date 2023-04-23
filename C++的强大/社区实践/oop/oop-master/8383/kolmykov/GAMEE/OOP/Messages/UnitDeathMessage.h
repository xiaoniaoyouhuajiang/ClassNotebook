#pragma once
#include "Message.h"
class UnitDeathMessage :
	public Message
{
private:
	int x;
	int y;
public:
	UnitDeathMessage();
	UnitDeathMessage(int x, int y);
	~UnitDeathMessage();
	std::string toString();
};


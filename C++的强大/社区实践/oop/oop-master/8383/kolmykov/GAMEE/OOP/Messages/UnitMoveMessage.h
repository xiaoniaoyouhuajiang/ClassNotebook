#pragma once
#include "Message.h"
class UnitMoveMessage :
	public Message
{
private:
	int x;
	int y;
public:
	UnitMoveMessage();
	UnitMoveMessage(int x, int y);
	~UnitMoveMessage();
	std::string toString();
};


#pragma once
#include "Message.h"
class UnitCreateMessage :
	public Message
{
private:
	int x;
	int y;
public:
	UnitCreateMessage();
	UnitCreateMessage(int x, int y);
	~UnitCreateMessage();
	std::string toString();
};


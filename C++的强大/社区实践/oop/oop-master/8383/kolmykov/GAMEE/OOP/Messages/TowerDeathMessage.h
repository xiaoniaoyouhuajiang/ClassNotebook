#pragma once
#include "Message.h"
class TowerDeathMessage :
	public Message
{
private:
	int x;
	int y;
public:
	TowerDeathMessage();
	TowerDeathMessage(int x, int y);
	~TowerDeathMessage();
	std::string toString();
};


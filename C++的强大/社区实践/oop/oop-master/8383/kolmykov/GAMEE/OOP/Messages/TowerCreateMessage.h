#pragma once
#include "Message.h"
class TowerCreateMessage :
	public Message
{
private:
	int x;
	int y;
public:
	TowerCreateMessage();
	TowerCreateMessage(int x, int y);
	~TowerCreateMessage();
	std::string toString();
};


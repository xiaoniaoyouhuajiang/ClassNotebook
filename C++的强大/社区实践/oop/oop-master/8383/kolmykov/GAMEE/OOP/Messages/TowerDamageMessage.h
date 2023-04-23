#pragma once
#include "Message.h"
class TowerDamageMessage :
	public Message
{
private:
	int x;
	int y;
	int damage;
public:
	TowerDamageMessage();
	TowerDamageMessage(int x, int y, int damage);
	~TowerDamageMessage();
	std::string toString();
};


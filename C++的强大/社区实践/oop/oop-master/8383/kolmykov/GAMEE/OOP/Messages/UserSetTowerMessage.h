#pragma once
#include "Message.h"
class UserSetTowerMessage :
	public Message
{
private:
	int x;
	int y;
public:
	UserSetTowerMessage();
	UserSetTowerMessage(int x, int y);
	~UserSetTowerMessage();
	std::string toString();
};


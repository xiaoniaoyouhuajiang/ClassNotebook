#pragma once
#include "Message.h"
class UserAttackMessage :
	public Message
{
private:
	int x;
	int y;
public:
	UserAttackMessage();
	UserAttackMessage(int x, int y);
	~UserAttackMessage();
	std::string toString();
};


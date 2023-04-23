#pragma once
#include "Message.h"
class UserCreateUnitMessage :
	public Message
{
private:
	int xU;
	int yU;
	int xT;
	int yT;
public:
	UserCreateUnitMessage();
	UserCreateUnitMessage(int xT, int yT, int xU, int yU);
	~UserCreateUnitMessage();
	std::string toString();
};


#pragma once
#include "Message.h"
class UserMoveMessage :
	public Message
{
private:
	int x;
	int y;
public:
	UserMoveMessage();
	UserMoveMessage(int x, int y);
	~UserMoveMessage();
	std::string toString();
};


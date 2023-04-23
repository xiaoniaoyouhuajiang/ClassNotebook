#pragma once
#include "Message.h"
class HandlerTowerNotExistMessage :
	public Message
{
public:
	HandlerTowerNotExistMessage();
	~HandlerTowerNotExistMessage();
	std::string toString();
};


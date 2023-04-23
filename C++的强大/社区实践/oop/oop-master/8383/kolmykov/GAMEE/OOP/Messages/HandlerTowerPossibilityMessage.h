#pragma once
#include "Message.h"
class HandlerTowerPossibilityMessage :
	public Message
{
public:
	HandlerTowerPossibilityMessage();
	~HandlerTowerPossibilityMessage();
	std::string toString();
};


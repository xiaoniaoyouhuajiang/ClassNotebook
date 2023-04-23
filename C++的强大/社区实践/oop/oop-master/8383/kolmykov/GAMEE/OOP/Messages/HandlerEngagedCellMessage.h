#pragma once
#include "Message.h"
class HandlerEngagedCellMessage :
	public Message
{
public:
	HandlerEngagedCellMessage();
	~HandlerEngagedCellMessage();
	std::string toString();
};


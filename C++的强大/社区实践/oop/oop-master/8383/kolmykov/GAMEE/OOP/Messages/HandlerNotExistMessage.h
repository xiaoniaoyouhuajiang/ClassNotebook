#pragma once
#include "Message.h"
class HandlerNotExistMessage :
	public Message
{
public:
	HandlerNotExistMessage();
	~HandlerNotExistMessage();
	std::string toString();
};


#pragma once
#include "Message.h"
class EndStepMessage :
	public Message
{
public:
	EndStepMessage();
	~EndStepMessage();
	std::string toString();
};


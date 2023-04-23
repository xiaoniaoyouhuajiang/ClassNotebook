#pragma once
#include <memory>
#include "Message.h"

class LogInterface
{
public:
	~LogInterface();
	virtual void log(std::shared_ptr<Message> message) = 0;
};


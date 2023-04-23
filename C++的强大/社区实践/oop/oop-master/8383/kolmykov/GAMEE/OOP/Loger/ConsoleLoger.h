#pragma once
#include "LogerProxy.h"
class ConsoleLoger :
	public LogerProxy
{
public:
	ConsoleLoger();
	ConsoleLoger(std::shared_ptr <Loger> loger);
	~ConsoleLoger();
	void log(std::shared_ptr<Message> message);
};


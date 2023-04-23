#pragma once
#include "LogerProxy.h"
class FileLoger :
	public LogerProxy
{
public:
	FileLoger();
	FileLoger(std::shared_ptr <Loger> loger);
	~FileLoger();
	void log(std::shared_ptr<Message> message);
};


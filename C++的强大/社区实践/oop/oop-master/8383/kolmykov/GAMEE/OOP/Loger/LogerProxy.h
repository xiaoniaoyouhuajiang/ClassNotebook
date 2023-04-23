#pragma once
#include "LogInterface.h"
#include "Loger.h"

class LogerProxy :
	public LogInterface
{
protected:
	std::shared_ptr<Loger> loger;
public:
	LogerProxy();
	LogerProxy(std::shared_ptr <Loger> loger);
	~LogerProxy();
	std::shared_ptr <Loger> getLoger();
	void setLoger(std::shared_ptr<Loger> loger);
	virtual void log(std::shared_ptr<Message> message);
};


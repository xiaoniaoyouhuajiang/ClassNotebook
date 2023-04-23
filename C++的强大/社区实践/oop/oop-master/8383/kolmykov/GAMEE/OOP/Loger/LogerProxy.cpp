#include "LogerProxy.h"

LogerProxy::LogerProxy() {

}

LogerProxy::LogerProxy(std::shared_ptr < Loger> loger)
{
	this->loger = loger;
}


LogerProxy::~LogerProxy()
{
}

std::shared_ptr<Loger> LogerProxy::getLoger()
{
	return loger;
}

void LogerProxy::setLoger(std::shared_ptr<Loger> loger)
{
	this->loger = loger;
}

void LogerProxy::log(std::shared_ptr<Message> message)
{
}

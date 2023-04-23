#include "ConsoleLoger.h"



ConsoleLoger::ConsoleLoger()
{
}

ConsoleLoger::ConsoleLoger(std::shared_ptr <Loger> loger):LogerProxy(loger)
{
}


ConsoleLoger::~ConsoleLoger()
{
}

void ConsoleLoger::log(std::shared_ptr<Message> message)
{
	loger->setLoggingToFile(false);
	loger->log(message);
}

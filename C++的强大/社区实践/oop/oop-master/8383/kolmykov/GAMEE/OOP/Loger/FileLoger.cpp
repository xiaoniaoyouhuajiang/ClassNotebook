#include "FileLoger.h"



FileLoger::FileLoger()
{
}

FileLoger::FileLoger(std::shared_ptr <Loger> loger) : LogerProxy(loger)
{
}


FileLoger::~FileLoger()
{
}

void FileLoger::log(std::shared_ptr<Message> message)
{
	loger->setLoggingToFile(true);
	loger->log(message);
}

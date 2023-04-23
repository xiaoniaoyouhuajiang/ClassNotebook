#include "Loger.h"



Loger::Loger()
{
	file = std::shared_ptr<std::ofstream>(new std::ofstream);
	file->open("logs.txt");
	_isFileLog = true;
}


Loger::~Loger()
{
	file->close();
}

void Loger::log(std::shared_ptr<Message> message) {
	if (_isFileLog) {
		*file << message->toString();
	}
	else {
		std::cout << message->toString();
	}
}

void Loger::setLoggingToFile(bool flag)
{
	_isFileLog = flag;
}

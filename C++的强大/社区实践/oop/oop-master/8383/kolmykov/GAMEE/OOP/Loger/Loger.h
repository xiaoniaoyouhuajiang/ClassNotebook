#pragma once
#include <iostream>
#include <fstream>
#include "Message.h"
#include "LogInterface.h"
class Loger : public LogInterface
{
private:
	std::shared_ptr<std::ofstream> file;
	bool _isFileLog;
public:
	Loger();
	~Loger();
	void log(std::shared_ptr<Message> message);
	void setLoggingToFile(bool flag);
};


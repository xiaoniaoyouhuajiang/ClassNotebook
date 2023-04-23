#pragma once
#include "LogInterface.h"
#include "RealLog.h"
class ProxyLog :
	public LogInterface
{
	bool debugMode;
	RealLog* realLog;

public:
	ProxyLog(bool debug, bool inConsole, bool inFile, bool fullInfo);
	virtual void log(std::string output);
	friend void operator<< (ProxyLog* log, const std::string& output);
	~ProxyLog();
};


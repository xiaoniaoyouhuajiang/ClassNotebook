#pragma once
#include "LogInterface.h"
#include "TimeStringAdapter.h"
class RealLog :
	public LogInterface
{
	bool debugMode;
	bool fullInfoMode;
	bool inConsoleMode;
	bool inFileMode;
	std::string curString;
	std::ofstream fOut;
public:
	RealLog() {}
	RealLog(bool debug, bool inConsole, bool inFile, bool fullInfo);

	virtual void log(std::string output);
	~RealLog();
};


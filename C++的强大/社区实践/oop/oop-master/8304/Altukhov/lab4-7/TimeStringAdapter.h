#pragma once
#include "LogInterface.h"
#include "AddTimeClass.h"
#include <iostream>

class TimeStringAdapter :
	public LogInterface
{
	bool debugMode;
	bool fullInfoMode;
	bool inConsoleMode;
	bool inFileMode;
	std::string curString;
	std::ofstream* fOut;

public:
	TimeStringAdapter() {}
	TimeStringAdapter(bool debug, bool inConsole, bool inFile, bool fullInfo, std::string& curString, std::ofstream* fOut) :debugMode(debug), fullInfoMode(fullInfo), inConsoleMode(inConsole), inFileMode(inFile), curString(curString), fOut(fOut) {};

	virtual void log(std::string output);
};


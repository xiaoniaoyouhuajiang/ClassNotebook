#include "pch.h"
#include "Proxy.h"


Proxy::Proxy(Recorder* write, bool logToFile, bool logToTerminal, bool withoutLog) {
	this->write = write;
	this->logToFile = logToFile;
	this->logToTerminal = logToTerminal;
	this->withoutLog = withoutLog;
}



bool Proxy::specificRequest(std::string str) {
	if (!withoutLog) 
		if (logToFile) {
			this->write->writeToFile(str);
		}
		if (logToTerminal) {
			this->write->writeToTerminal(str);
		}
	return true;
}

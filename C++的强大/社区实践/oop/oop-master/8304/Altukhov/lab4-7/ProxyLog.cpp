#include "ProxyLog.h"


ProxyLog::ProxyLog(bool debug, bool inConsole, bool inFile, bool fullInfo) {
	debugMode = debug;

	realLog = new RealLog(debug, inConsole, inFile, fullInfo);

}
void ProxyLog::log(std::string output) {
	
	if (!debugMode) {
		return;
	}
	realLog->log(output);
}
void operator<< (ProxyLog* log, const std::string& output) {
	if (!log->debugMode) {
		return;
	}
	log->realLog->log(output);
}
ProxyLog::~ProxyLog() {
	delete realLog;
}

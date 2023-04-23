#include "RealLog.h"
RealLog::RealLog(bool debug, bool inConsole, bool inFile, bool fullInfo) {
	debugMode = debug;
	fullInfoMode = fullInfo;
	inConsoleMode = inConsole;
	inFileMode = inFile;

	if (inFileMode) {
		fOut.open("output.txt");
	}
}
void RealLog::log(std::string output) {

	curString = output;
	if (fullInfoMode) {
		TimeStringAdapter adapter(debugMode, inConsoleMode, inFileMode, fullInfoMode, curString, &fOut);
		adapter.log(output);
		return;
	}
	if (inConsoleMode) {
		//RealLog* logLink = const_cast<RealLog*>(this);
		std::cout << output;
	}
	if (inFileMode) {
		fOut << output;
	}
}

RealLog::~RealLog() {
	if (inFileMode) {
		fOut.close();
	}
}

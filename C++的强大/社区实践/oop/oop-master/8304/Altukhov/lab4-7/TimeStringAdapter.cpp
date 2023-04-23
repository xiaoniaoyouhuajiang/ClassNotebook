#include "TimeStringAdapter.h"

void TimeStringAdapter::log(std::string output)
{
	AddTimeClass timeManager;
	std::string newStr = timeManager.addTime(output);
	if (inConsoleMode) {
		std::cout << newStr;
	}
	if (inFileMode) {
		*fOut << newStr;
	}
}

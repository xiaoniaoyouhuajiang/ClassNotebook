#pragma once
#include <string>
#include <ctime>
class AddTimeClass
{
public:
	std::string addTime (std::string& output) {
		time_t t;
		struct tm buf;

		time(&t);
		//timeinfo = localtime(&rawtime);
		localtime_s(&buf ,&t);

		char str[26];
		asctime_s(str, sizeof str, &buf);
		std::string toString = (std::string)str;
		toString.erase(toString.find('\n'), 1);

		return toString + " " + output;

	}
};


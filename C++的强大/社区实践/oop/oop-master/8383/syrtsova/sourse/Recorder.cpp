#include "pch.h"
#include "Recorder.h"



Recorder::Recorder() {
	out.open("./log.txt", std::ios_base::out | std::ios_base::app);
}
Recorder::~Recorder() {
	out.close();
}

/*
std::ostream& operator << (std::ostream& out, std::string str) {
	out << str << std::endl;
	return out;
}
*/

bool Recorder::writeToFile(std::string str) {
	if (out.is_open())
	{
		out << str << std::endl;
	}
	return true;
}

bool Recorder::writeToTerminal(std::string str) {
	std::cout << str << std::endl;
	return true;
}



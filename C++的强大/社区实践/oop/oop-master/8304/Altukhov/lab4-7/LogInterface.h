#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
class LogInterface
{

public:

	virtual void log(std::string output) = 0;
};


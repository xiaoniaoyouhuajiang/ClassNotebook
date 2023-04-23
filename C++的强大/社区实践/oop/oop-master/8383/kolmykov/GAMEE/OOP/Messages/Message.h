#pragma once
#include <string>
#include <sstream>
class Message
{
public:
	Message();
	~Message();
	virtual std::string toString();
};


#pragma once
#include <string>

/// ÷ель

/**
* ÷елевой класс, объ€лв€ет интерфейс, с которым может работать клиенский код
*/
 
class Target
{
public:
	virtual ~Target() = default;
	virtual bool request(std::string str){
		return true;
	}
};

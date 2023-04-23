#pragma once
#include "Land.h"
class CommonLand :
	public Land
{
public:
	CommonLand();
	~CommonLand();
	void bufUnit(std::shared_ptr<Unit> unit);
	char getChar() override;
     std::string getPath() override;
};


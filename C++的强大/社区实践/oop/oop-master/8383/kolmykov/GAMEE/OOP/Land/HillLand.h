#pragma once
#include "Land.h"
class HillLand :
	public Land
{
public:
	HillLand();
	~HillLand();
	void bufUnit(std::shared_ptr<Unit> unit);
	char getChar() override;
    std::string getPath() override;
};


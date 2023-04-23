#pragma once
#include "Land.h"


class GrassLand :
	public Land
{
public:
	GrassLand();
	~GrassLand();
	void bufUnit(std::shared_ptr<Unit> unit);
	char getChar() override;
    std::string getPath() override;
};


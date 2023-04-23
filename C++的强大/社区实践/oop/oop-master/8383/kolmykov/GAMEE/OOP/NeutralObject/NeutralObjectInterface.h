#pragma once
#include <memory>
//#include "Unit.h"


class Unit;

class NeutralObjectInterface
{
public:
	NeutralObjectInterface();
	~NeutralObjectInterface();
	virtual void affectOnUnit(std::shared_ptr<Unit> unit) = 0;
};


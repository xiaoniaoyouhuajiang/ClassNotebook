#pragma once
#include "Unit.h"
#include <memory>
#include "UnitType.h"


class UnitFactory
{
protected:
    Kind kind;
	UnitType type;
public:
	UnitFactory();
	~UnitFactory();
	virtual std::shared_ptr<Unit> create(int x, int y, int level);
	UnitType getType();
    Kind getKind();
    virtual std::string getPath();
};

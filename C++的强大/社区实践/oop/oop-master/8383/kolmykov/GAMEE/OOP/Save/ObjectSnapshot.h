#pragma once
#include "ObjectType.h"


class ObjectSnapshot
{
private:
	ObjectType type;
public:
	ObjectSnapshot(ObjectType type);
	~ObjectSnapshot();
	ObjectType getType();
};


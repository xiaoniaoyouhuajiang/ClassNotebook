#include "ObjectSnapshot.h"



ObjectSnapshot::ObjectSnapshot(ObjectType type) : type(type)
{
}


ObjectSnapshot::~ObjectSnapshot()
{
}

ObjectType ObjectSnapshot::getType()
{
	return type;
}

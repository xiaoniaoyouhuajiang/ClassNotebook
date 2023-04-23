#include "NeutralObject.h"
//#include "Unit.h"
#include "AffectBehavior.h"


NeutralObject::NeutralObject()
{
}


NeutralObject::~NeutralObject()
{
}

void NeutralObject::affectOnUnit(std::shared_ptr<Unit> unit) {
	affectBehavior->affect(unit);
}

std::shared_ptr<ObjectSnapshot> NeutralObject::getSnapshot()
{
	return std::shared_ptr<ObjectSnapshot>(new ObjectSnapshot(type));
}

void NeutralObject::operator+=(std::shared_ptr<Unit> unit)
{
	affectOnUnit(unit);
}


std::string NeutralObject::getPath() {
    return "";
}

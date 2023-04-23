#pragma once
#include "NeutralObjectInterface.h"
#include "ObjectType.h"
#include "ObjectSnapshot.h"
#include <string>>

class AffectBehavior;
class Unit;


class NeutralObject : NeutralObjectInterface
{
protected:
	std::shared_ptr<AffectBehavior> affectBehavior;
	ObjectType type;
public:
	NeutralObject();
	~NeutralObject();
	virtual void affectOnUnit(std::shared_ptr<Unit> unit);
	std::shared_ptr<ObjectSnapshot> getSnapshot();
	void operator +=(std::shared_ptr<Unit> unit);
    virtual std::string getPath();
};


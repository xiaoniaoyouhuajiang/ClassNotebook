#include "NeutralObjects.h"

NeutralObject ArmourUpgrader::getType()
{
	return NeutralObject::ARMOURUPGRADER;
}

NeutralObject Spikes::getType()
{
	return NeutralObject::SPIKES;
}

NeutralObject AttackUpgrader::getType()
{
	return NeutralObject::ATTACKUPGRADER;
}

NeutralObject Hospital::getType()
{
	return NeutralObject::HOSPITAL;
}

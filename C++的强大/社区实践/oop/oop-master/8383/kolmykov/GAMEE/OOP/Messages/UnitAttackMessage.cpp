#include "UnitAttackMessage.h"



UnitAttackMessage::UnitAttackMessage()
{
}

UnitAttackMessage::UnitAttackMessage(int x, int y)
{
	this->x = x;
	this->y = y;
}


UnitAttackMessage::~UnitAttackMessage()
{
}

std::string UnitAttackMessage::toString()
{
	std::ostringstream os;
	os << "Attack by unit with coordinates  (" << x << " ; " << y << ")\n";
	return os.str();
}

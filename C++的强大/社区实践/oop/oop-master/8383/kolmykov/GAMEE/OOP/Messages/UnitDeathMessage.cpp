#include "UnitDeathMessage.h"



UnitDeathMessage::UnitDeathMessage()
{
}

UnitDeathMessage::UnitDeathMessage(int x, int y)
{
	this->x = x;
	this->y = y;
}


UnitDeathMessage::~UnitDeathMessage()
{
	
}

std::string UnitDeathMessage::toString()
{
	std::ostringstream os;
	os << "Unit with coordinates (" << x << " ; " << y << ") has died\n";
	return os.str();
}

#include "UnitCreateMessage.h"



UnitCreateMessage::UnitCreateMessage()
{
}

UnitCreateMessage::UnitCreateMessage(int x, int y)
{
	this->x = x;
	this->y = y;
}


UnitCreateMessage::~UnitCreateMessage()
{
}

std::string UnitCreateMessage::toString()
{
	std::ostringstream os;
	os << "Unit was created with coordinates  (" << x << " ; " << y << ")\n";
	return os.str();
}

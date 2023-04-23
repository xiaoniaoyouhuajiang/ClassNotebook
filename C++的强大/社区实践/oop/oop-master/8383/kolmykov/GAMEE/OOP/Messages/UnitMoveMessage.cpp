#include "UnitMoveMessage.h"



UnitMoveMessage::UnitMoveMessage()
{
}

UnitMoveMessage::UnitMoveMessage(int x, int y)
{
	this->x = x;
	this->y = y;
}


UnitMoveMessage::~UnitMoveMessage()
{
}

std::string UnitMoveMessage::toString()
{
	std::ostringstream os;
	os << "Unit has moved to coordinates  (" << x << " ; " << y << ")\n";
	return os.str();
}

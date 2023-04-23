#include "UserMoveMessage.h"



UserMoveMessage::UserMoveMessage()
{
}

UserMoveMessage::UserMoveMessage(int x, int y)
{
	this->x = x;
	this->y = y;
}


UserMoveMessage::~UserMoveMessage()
{
}

std::string UserMoveMessage::toString()
{
	std::ostringstream os;
	os << "Movement caused by unit with coordinates  (" << x << " ; " << y << ")\n";
	return os.str();
}
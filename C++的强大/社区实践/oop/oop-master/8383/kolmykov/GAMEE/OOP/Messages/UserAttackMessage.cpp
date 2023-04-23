#include "UserAttackMessage.h"



UserAttackMessage::UserAttackMessage()
{
}

UserAttackMessage::UserAttackMessage(int x, int y)
{
	this->x = x;
	this->y = y;
}


UserAttackMessage::~UserAttackMessage()
{
}

std::string UserAttackMessage::toString()
{
	std::ostringstream os;
	os << "Attack caused by unit with coordinates  (" << x << " ; " << y << ")\n";
	return os.str();
}

#include "UserSetTowerMessage.h"



UserSetTowerMessage::UserSetTowerMessage()
{
}

UserSetTowerMessage::UserSetTowerMessage(int x, int y)
{
	this->x = x;
	this->y = y;
}


UserSetTowerMessage::~UserSetTowerMessage()
{
}

std::string UserSetTowerMessage::toString()
{
	std::ostringstream os;
	os << "Attempt to create tower in coordinates  (" << x << " ; " << y << ")\n";
	return os.str();
}

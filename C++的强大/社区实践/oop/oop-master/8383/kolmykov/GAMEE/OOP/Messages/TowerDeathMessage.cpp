#include "TowerDeathMessage.h"



TowerDeathMessage::TowerDeathMessage()
{
}

TowerDeathMessage::TowerDeathMessage(int x, int y)
{
	this->x = x;
	this->y = y;
}


TowerDeathMessage::~TowerDeathMessage()
{
}

std::string TowerDeathMessage::toString()
{
	std::ostringstream os;
	os << "Tower with coordinates  (" << x << " ; " << y << ") has been destroyed\n";
	return os.str();
}

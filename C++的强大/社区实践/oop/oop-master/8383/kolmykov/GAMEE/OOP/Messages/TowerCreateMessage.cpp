#include "TowerCreateMessage.h"



TowerCreateMessage::TowerCreateMessage()
{
}

TowerCreateMessage::TowerCreateMessage(int x, int y)
{
	this->x = x;
	this->y = y;
}


TowerCreateMessage::~TowerCreateMessage()
{
}

std::string TowerCreateMessage::toString()
{
	std::ostringstream os;
	os << "Tower was created with coordinates  (" << x << " ; " << y << ")\n";
	return os.str();
}

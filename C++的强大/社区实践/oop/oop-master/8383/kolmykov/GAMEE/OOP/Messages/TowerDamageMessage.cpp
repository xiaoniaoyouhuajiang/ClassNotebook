#include "TowerDamageMessage.h"



TowerDamageMessage::TowerDamageMessage()
{
}

TowerDamageMessage::TowerDamageMessage(int x, int y, int damage)
{
	this->x = x;
	this->y = y;
	this->damage = damage;
}


TowerDamageMessage::~TowerDamageMessage()
{
}

std::string TowerDamageMessage::toString()
{
	std::ostringstream os;
	os << "Tower with coordinates  (" << x << " ; " << y << ") has got damage = " << damage << "\n";
	return os.str();
}

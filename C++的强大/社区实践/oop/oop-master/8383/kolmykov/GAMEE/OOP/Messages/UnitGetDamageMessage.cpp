#include "UnitGetDamageMessage.h"



UnitGetDamageMessage::UnitGetDamageMessage()
{
}

UnitGetDamageMessage::UnitGetDamageMessage(int x, int y, int damage)
{
	this->x = x;
	this->y = y;
	this->damage = damage;
}


UnitGetDamageMessage::~UnitGetDamageMessage()
{
}

std::string UnitGetDamageMessage::toString()
{
	std::ostringstream os;
	os << "Attack to unit with coords (" << x << " ; " << y << ") with damage = " << damage << "\n";
	return os.str();
}

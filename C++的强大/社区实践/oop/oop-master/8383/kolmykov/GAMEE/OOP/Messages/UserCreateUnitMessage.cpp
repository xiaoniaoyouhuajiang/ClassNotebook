#include "UserCreateUnitMessage.h"



UserCreateUnitMessage::UserCreateUnitMessage()
{
}

UserCreateUnitMessage::UserCreateUnitMessage(int xT, int yT, int xU, int yU)
{
	this->xT = xT;
	this->yT = yT;
	this->xU = xU;
	this->yU = yU;
}


UserCreateUnitMessage::~UserCreateUnitMessage()
{
}

std::string UserCreateUnitMessage::toString()
{
	std::ostringstream os;
	os << "Attempt to create a unit from a tower with coordinates (" << xT << " ; " << yT << ") in coordinates (" << xU << " ; " << yU << ")\n";
	return os.str();
}

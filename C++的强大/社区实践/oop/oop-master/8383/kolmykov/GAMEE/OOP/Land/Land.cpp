#include "Land.h"
#include "Unit.h"


Land::Land() {

}


Land::~Land() {

}

void Land::bufUnit(std::shared_ptr<Unit> unit)
{
}

char Land::getChar()
{
	return '0';
}


LandType Land::getType() {
	return type;
}


std::string Land::getPath() {
    return "";
}

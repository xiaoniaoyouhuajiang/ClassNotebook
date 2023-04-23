#include "TowerStatusMessage.h"



TowerStatusMessage::TowerStatusMessage()
{
}

TowerStatusMessage::TowerStatusMessage(std::shared_ptr<Tower> tower)
{
	this->tower = tower;
}


TowerStatusMessage::~TowerStatusMessage()
{
}

std::string TowerStatusMessage::toString()
{
	std::ostringstream os;
	//os << "Tower state: hp = " << tower->getHP() << " level = " << tower->getLevel() << "damage = " << tower->getDamage() << " size = " << tower->getSize();
	os << tower;
	return os.str();
}

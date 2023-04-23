#pragma once
#include "Message.h"
#include "Tower.h"
class TowerStatusMessage :
	public Message
{
private:
	std::shared_ptr<Tower> tower;
public:
	TowerStatusMessage();
	TowerStatusMessage(std::shared_ptr<Tower> tower);
	~TowerStatusMessage();
	std::string toString();
};


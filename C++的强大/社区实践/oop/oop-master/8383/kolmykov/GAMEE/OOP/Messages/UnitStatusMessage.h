#pragma once
#include "Message.h"
#include "Unit.h"
class UnitStatusMessage :
	public Message
{
private:
	std::shared_ptr<Unit> unit;
public:
	UnitStatusMessage();
	UnitStatusMessage(std::shared_ptr<Unit> unit);
	~UnitStatusMessage();
	std::string toString();
};


#include "Player.h"

PlayerBase::PlayerBase(RuleBase* rule) : rule(rule)
{}

size_t PlayerBase::getNumber()
{
	return number;
}


Player1::Player1(RuleBase* rule) : PlayerBase(rule)
{
	number = 1;
}

Player2::Player2(RuleBase* rule) : PlayerBase(rule)
{
	number = 2;
}

Player3::Player3(RuleBase* rule) : PlayerBase(rule)
{
}

#include "Commands.h"

void CommandBase::setLogProxy(LogProxy* log_)
{
	log = log_;
}

void CommandBase::setLogType(LogTypes type)
{
	(*log).loadLogType(type);
}

void AddingCommand::setParams(std::string name_, Point p_)
{
	name = name_;
	p = p_;
}

void AddingCommand::execute()
{
	(*log).addInfoAboutUnitAdding(name, p);
}

void MovingCommand::setParams(std::string name_, Point from_, Point to_)
{
	name = name_;
	from = from_;
	to = to_;
}

void MovingCommand::execute()
{
	(*log).addInfoAboutMovingUnit(name, from, to);
}

void AttackicngCommand::setParams(std::string name1_, std::string name2_, size_t how_, takeDamageResult res_)
{
	name1 = name1_;
	name2 = name2_;
	how = how_;
	res = res_;
}

void AttackicngCommand::execute()
{
	(*log).addInfoAboutUnitAttack(name1, name2, how, res);
}

void NotifyCommand::execute()
{
	(*log).addInfoAboutBaseNotify();
}

#pragma once
#include "Log.h"
#include "Resourses.h"

struct CommandsInterface
{
	virtual void execute() = 0;

	void setLogProxy(LogProxy* log_);
	void setLogType(LogTypes type);

protected:
	LogProxy* log = nullptr;
};

struct MovingCommand : CommandsInterface
{
	void setParams(std::string name_, Point from_, Point to_);
	void execute();

private:
	std::string name;
	Point from = {0, 0};
	Point to = {0, 0};
};


struct AddingCommand : CommandsInterface
{
	void setParams(std::string name_, Point p_);
	void execute();

private:
	std::string name;
	Point p = {0, 0};
};


struct AttackicngCommand : CommandsInterface
{
	void setParams(std::string name1_, std::string name2_, size_t how_, takeDamageResult res_);
	void execute();

private:
	std::string name1;
	std::string name2;
	size_t how = 0;
	takeDamageResult res = takeDamageResult::damageTaken;
};

struct NotifyCommand : CommandsInterface
{
	void execute();
};
#include "Loggs.h"

LogProxy::LogProxy(LogTypes type)
{
	this->type = type;
	switch (type)
	{
	case LogTypes::File:
		cur = new FileLog;
		break;
	case LogTypes::Terminal:
		cur = new TerminalLog;
		break;
	case LogTypes::No:
		cur = nullptr;
		break;
	default:
		break;
	}
}

void LogProxy::writeAboutUnitCreating(int x, int y, std::string name)
{
	if (cur != nullptr)
		cur->writeAboutUnitCreating(x, y, name);
}

void LogProxy::writeAboutUnitMoving(int x_from, int y_from, int x_to, int y_to)
{
	if (cur != nullptr)
		cur->writeAboutUnitMoving(x_from, y_from, x_to, y_to);
}

void LogProxy::writeAboutUnitRemoving(int x, int y)
{
	if (cur != nullptr)
		cur->writeAboutUnitRemoving(x, y);
}

void LogProxy::writeAboutBaseCreating(int x, int y)
{
	if (cur != nullptr)
		cur->writeAboutBaseCreating(x, y);
}

void LogProxy::show()
{
	switch (type)
	{
	case LogTypes::File:
	{
		std::ofstream out("log.txt");
		out << (*cur);
		out.close();
		break;
	}
	case LogTypes::Terminal:
		std::cout << (*cur);
		break;
	case LogTypes::No:
		break;
	default:
		break;
	}
}

void LogBase::writeAboutUnitCreating(int x, int y, std::string name)
{
	data += name + " was created in base with coordinates - " + std::to_string(x) +  " " +  std::to_string(y) + " \n";
}

void LogBase::writeAboutUnitMoving(int x_from, int y_from, int x_to, int y_to)
{
	data += "Unit was moved from " + std::to_string(x_from) + " " + std::to_string(y_from) + " to " +
		std::to_string(x_to) + " " + std::to_string(y_to) + " \n";
}

void LogBase::writeAboutUnitRemoving(int x, int y)
{
	data += "Unit was removed from " + std::to_string(x) + " " + std::to_string(y) + " \n";
}

void LogBase::writeAboutBaseCreating(int x, int y)
{
	data += "Base was added to " + std::to_string(x) + " " + std::to_string(y) + " \n";
}

std::ostream& LogAdapter::execute(std::ostream& out)
{
	std::ofstream out2("log.txt");

	return out2;
}


std::ostream& operator<<(std::ostream& out, LogBase& log)
{
	out << log.data;

	return out;
}


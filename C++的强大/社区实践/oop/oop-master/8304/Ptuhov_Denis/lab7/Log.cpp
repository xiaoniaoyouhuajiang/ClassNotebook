#include "Log.h"

void LogProxy::loadLogType(LogTypes type)
{
	this->type = type;
}

void LogProxy::addInfoAboutUnitAdding(std::string& unitName, Point p)
{
	switch (type)
	{
	case LogTypes::File:
		lgf.addInfoAboutUnitAdding(unitName, p);
		break;
	case LogTypes::Terminal:
		lgt.addInfoAboutUnitAdding(unitName, p);
		break;
	case LogTypes::No:
		return;
	}

	int G = 0;
}

void LogProxy::addInfoAboutMovingUnit(std::string& unitName, Point from, Point to)
{
	switch (type)
	{
	case LogTypes::File:
		lgf.addInfoAboutMovingUnit(unitName, from, to);
		break;
	case LogTypes::Terminal:
		lgt.addInfoAboutMovingUnit(unitName, from, to);
		break;
	case LogTypes::No:
		return;
	}
}


void LogProxy::addInfoAboutUnitAttack(std::string& unitWho, std::string& unitWhom, size_t damage, takeDamageResult res)
{
	switch (type)
	{
	case LogTypes::File:
		lgf.addInfoAboutUnitAttack(unitWho, unitWhom, damage, res);
		break;
	case LogTypes::Terminal:
		lgt.addInfoAboutUnitAttack(unitWho, unitWhom, damage, res);
		break;
	case LogTypes::No:
		return;
	}
}

void LogProxy::addInfoAboutBaseNotify()
{
	switch (type)
	{
	case LogTypes::File:
		lgf.addInfoAboutBaseNotify();
		break;
	case LogTypes::Terminal:
		lgt.addInfoAboutBaseNotify();
		break;
	case LogTypes::No:
		break;
	}
}

void LogToFile::addInfoAboutUnitAdding(std::string& unitName, Point p)
{
	data += std::to_string(oper_num) + ") " + unitName + " was added to point"
		+ " (" + std::to_string(p.x) + "; " + std::to_string(p.y) + ")\n";
	
	++oper_num;
}

void LogToFile::addInfoAboutMovingUnit(std::string& unitName, Point from, Point to)
{
	data += std::to_string(oper_num) + ") " + unitName + " was moved from " +
		+"(" + std::to_string(from.x) + "; " + std::to_string(from.y) + ") to " +
		+"(" + std::to_string(to.x) + "; " + std::to_string(to.y) + ")\n";

	++oper_num;
}

void LogToFile::addInfoAboutUnitAttack(std::string& unitWho, std::string& unitWhom, size_t damage, takeDamageResult res)
{
	data += std::to_string(oper_num) + ") " + unitWho + " attacked(" + std::to_string(damage) + " damage) " + unitWhom;

	switch (res)
	{
	case takeDamageResult::damageTaken:
		break;
	case takeDamageResult::block:
		data += "\nBut damage blocked\n";
		break;
	case takeDamageResult::dodge:
		data += "\nBut damage dodged\n";
		break;
	case takeDamageResult::death:
		data += "\n" + unitWhom + " died\n";
		break;
	default:
		break;
	}

	++oper_num;
}

void LogToFile::addInfoAboutBaseNotify()
{
	data += std::to_string(oper_num) + ") " + "Base baff was used (+20 damage)\n";
	 
	++oper_num;
}

void LogToTerminal::addInfoAboutUnitAdding(std::string& unitName, Point p)
{
	data += std::to_string(oper_num) + ") " + unitName + " was added to point"
		+ " (" + std::to_string(p.x) + "; " + std::to_string(p.y) + ")\n";

	++oper_num;
}

void LogToTerminal::addInfoAboutMovingUnit(std::string& unitName, Point from, Point to)
{
	data += std::to_string(oper_num) + ") " + unitName + " was moved from " +
		+"(" + std::to_string(from.x) + "; " + std::to_string(from.y) + ") to " +
		+"(" + std::to_string(to.x) + "; " + std::to_string(to.y) + ")\n";

	++oper_num;
}

void LogToTerminal::addInfoAboutUnitAttack(std::string& unitWho, std::string& unitWhom, size_t damage, takeDamageResult res)
{
	data += std::to_string(oper_num) + ") " + unitWho + " attacked(" + std::to_string(damage) + " damage) " + unitWhom ;

	switch (res)
	{
	case takeDamageResult::damageTaken:
		data += "\nDamage taken\n";
		break;
	case takeDamageResult::block:
		data += "\nBut damage blocked\n";
		break;
	case takeDamageResult::dodge:
		data += "\nBut damage dodged\n";
		break;
	case takeDamageResult::death:
		data += "\n" + unitWhom + " died\n";
		break;
	default:
		break;
	}

	++oper_num;
}

std::ofstream& operator<<(std::ofstream& out, LogToFile log)
{
	out << log.data;
	return out;
}

std::ostream& operator<<(std::ostream& out, LogToTerminal log)
{
	out << log.data;
	return out;
}

std::ostream& operator<<(std::ostream& out, LogProxy log)
{
	switch (log.type)
	{
	case LogTypes::File:
	{
		std::ofstream out("log.txt");
		out << log.lgf;
		break;
	}
	case LogTypes::Terminal:
		out << log.lgt;
		break;
	case LogTypes::No:
		break;
	}

	return out;
}

std::ofstream& LogAdapter::fromTerminalToFile(std::ostream& out)
{
	return dynamic_cast<std::ofstream&>(out);
}

void LogToTerminal::addInfoAboutBaseNotify()
{
	data += "Base baff was used (+20 damage)\n";
}

#include "Logger.h"


FileLogger::FileLogger()
{
	fileToLogSream.open("log.txt");
}

FileLogger::~FileLogger()
{
	fileToLogSream.close();
}

void FileLogger::logInformation(std::string logStr)
{
	fileToLogSream << logStr;
	fileToLogSream << std::endl;
}

void FileLogger::stopLogging()
{
	fileToLogSream << infoToLog;
}

void FileLogger::logBaseAttacked(Base* base)
{
	fileToLogSream << base << std::endl;
}

void FileLogger::logUnitAttacked(IUnit* unit)
{
	fileToLogSream << unit << std::endl;
}

LoggerProxy::LoggerProxy(LoggerType type)
{
	if (type == LoggerType::TERMINAL) {
		lType = LoggerType::TERMINAL;
		logger = new TerminalLogger();
	}
	else if (type == LoggerType::FILE) {
		lType = LoggerType::FILE;
		logger = new FileLogger();
	}
	else {
		lType = LoggerType::EMPTYLOGGER;
		logger = new EmptyLogger();
	}
}

LoggerProxy::~LoggerProxy()
{
}

void LoggerProxy::logInformation(std::string logStr)
{
	logger->logInformation(logStr);
}

void LoggerProxy::stopLogging()
{
	logger->stopLogging();
}

void LoggerProxy::logBaseAttacked(Base* base)
{
	logger->logBaseAttacked(base);
}

void LoggerProxy::logUnitAttacked(IUnit* unit)
{
	logger->logUnitAttacked(unit);
}

void LoggerProxy::changeLogger(LoggerType type)
{
	if (type == LoggerType::TERMINAL) {
		lType = LoggerType::TERMINAL;
		logger = new TerminalLogger();
	}
	else if (type == LoggerType::FILE) {
		lType = LoggerType::FILE;
		logger = new FileLogger();
	}
	else {
		lType = LoggerType::EMPTYLOGGER;
		logger = new EmptyLogger();
	}
}


void TerminalLogger::logInformation(std::string logStr)
{
	infoToLog += logStr;
	infoToLog += "\n";
}

void TerminalLogger::stopLogging()
{
	std::cout << infoToLog;
}

void TerminalLogger::logBaseAttacked(Base* base)
{
	std::cout << "Base " << base->getBaseNum() << " was attacked, " << base << std::endl;
}

void TerminalLogger::logUnitAttacked(IUnit* unit)
{
	std::cout << "Unit was attacked, " << unit << std::endl;
}


void EmptyLogger::stopLogging()
{

}

void EmptyLogger::logInformation(std::string logStr)
{
}

void EmptyLogger::logBaseAttacked(Base* base)
{
}

void EmptyLogger::logUnitAttacked(IUnit* unit)
{
}

std::ostream& operator<<(std::ostream& out, Base* base)
{
	out << "Base condition: team - " << base->getBaseNum() << ",  health - " << base->getHealth() << ", num units from base - " << base->getNumUnitsFromBase();
	return out;
}

std::ostream& operator<<(std::ostream& out, IUnit* unit)
{
	out << "Unit condition: team - " << unit->getTeam() << ",  health - " << unit->getHealth() << ", armour - " << unit->getArmour();
	return out;
}

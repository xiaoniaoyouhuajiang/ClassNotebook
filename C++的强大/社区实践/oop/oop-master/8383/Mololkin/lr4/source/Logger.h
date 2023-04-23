#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "IUnit.h"
#include "Base.h"

std::ostream& operator<< (std::ostream& out, Base* base);
std::ostream& operator<< (std::ostream& out, IUnit* unit);

enum class LoggerType {
	TERMINAL,
	FILE,
	EMPTYLOGGER,
};

class ILogger {
public:
	virtual void logInformation(std::string logStr) = 0;
	virtual void stopLogging() = 0;
	virtual void logBaseAttacked(Base* base) = 0;
	virtual void logUnitAttacked(IUnit* unit) = 0;
};

class TerminalLogger : public ILogger{
private: 
	std::string infoToLog;
public:
	void logInformation(std::string logStr) override;
	void stopLogging() override;
	void logBaseAttacked(Base* base) override;
	void logUnitAttacked(IUnit* unit) override;
};

class FileLogger : public ILogger {
private:
	std::string infoToLog;
	std::ofstream fileToLogSream;
public:
	FileLogger();
	~FileLogger();
	void logInformation(std::string logStr) override;
	void stopLogging() override;
	void logBaseAttacked(Base* base) override;
	void logUnitAttacked(IUnit* unit);
};

class EmptyLogger : public ILogger {
public:
	void stopLogging() override;
	void logInformation(std::string logStr) override;
	void logBaseAttacked(Base* base) override;
	void logUnitAttacked(IUnit* unit) override;
};

class LoggerProxy
{
private:
	ILogger* logger;
	LoggerType lType;
public:
	LoggerProxy(LoggerType type);
	~LoggerProxy();
	void logInformation(std::string logStr);
	void stopLogging();
	void logBaseAttacked(Base* base);
	void logUnitAttacked(IUnit* unit);
	void changeLogger(LoggerType type);

};



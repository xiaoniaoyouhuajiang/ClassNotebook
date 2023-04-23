#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Resourses.h"

struct LogInterface
{
	virtual void addInfoAboutUnitAdding(std::string& unitName, Point p) = 0;
	virtual void addInfoAboutMovingUnit(std::string& unitName, Point from, Point to) = 0;
	virtual void addInfoAboutUnitAttack(std::string& unitWho, std::string& unitWhom, size_t damage, takeDamageResult res) = 0;
	virtual void addInfoAboutBaseNotify() = 0;
};

struct LogToFile : LogInterface
{
	void addInfoAboutUnitAdding(std::string& unitName, Point p);
	void addInfoAboutMovingUnit(std::string& unitName, Point from, Point to);
	void addInfoAboutUnitAttack(std::string& unitWho, std::string& unitWhom, size_t damage, takeDamageResult res);
	void addInfoAboutBaseNotify();
	
	friend std::ofstream& operator<<(std::ofstream& out, LogToFile log);

private:
	size_t oper_num = 1;
	std::string data;
};

struct LogToTerminal : LogInterface
{
	void addInfoAboutUnitAdding(std::string& unitName, Point p);
	void addInfoAboutMovingUnit(std::string& unitName, Point from, Point to);
	void addInfoAboutUnitAttack(std::string& unitWho, std::string& unitWhom, size_t damage, takeDamageResult res);
	void addInfoAboutBaseNotify();

	friend std::ostream& operator<<(std::ostream& out, LogToTerminal log);

private:
	size_t oper_num = 1;
	std::string data;
};

struct LogAdapter
{
	std::ofstream& fromTerminalToFile(std::ostream& out);
};

struct LogProxy : LogInterface
{
	void loadLogType(LogTypes type);

	void addInfoAboutUnitAdding(std::string& unitName, Point p);
	void addInfoAboutMovingUnit(std::string& unitName, Point from, Point to);
	void addInfoAboutUnitAttack(std::string& unitWho, std::string& unitWhom, size_t damage, takeDamageResult res);
	void addInfoAboutBaseNotify();

	friend std::ostream& operator<<(std::ostream& out, LogProxy log);

private:
	LogTypes type = LogTypes::No;
	LogToFile lgf;
	LogToTerminal lgt;
	LogAdapter adapter;
};


#pragma once
#include <string>
#include <iostream>
#include <fstream>

enum class LogTypes
{
	File,
	Terminal,
	No
};

class LogBase
{
protected:
	std::string data;
public:
	virtual void writeAboutUnitCreating(int x, int y, std::string name);
	virtual void writeAboutUnitMoving(int x_from, int y_from, int x_to, int y_to);
	virtual void writeAboutUnitRemoving(int x, int y);
	virtual void writeAboutBaseCreating(int x, int y);

	friend std::ostream& operator<<(std::ostream& out, LogBase& log);
};

class LogAdapter
{
public:
	std::ostream& execute(std::ostream& out);
};

class FileLog : public LogBase
{
};


class TerminalLog : public LogBase
{
};


class LogProxy : public LogBase
{
	LogBase* cur = nullptr;
	LogTypes type;
public:
	LogProxy(LogTypes);

	void writeAboutUnitCreating(int x, int y, std::string name);
	void writeAboutUnitMoving(int x_from, int y_from, int x_to, int y_to);
	void writeAboutUnitRemoving(int x, int y);
	void writeAboutBaseCreating(int x, int y);

	void show();
};
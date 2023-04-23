#pragma once

#include <string>
#include <map>
#include <iostream>
#include <memory>

#include <GAME/log/LogAdapter.hpp>
#include <GAME/log/LogInfo.hpp>

using std::string;
using std::map;
using std::ostream;
using std::pair;
using std::shared_ptr;

class Log;
class LogInfo;

class Loggable {
private:
	LogInfo _logInfo;

protected:
	virtual void fillLogInfo(LogInfo& info) = 0;

public:
	LogInfo& makeLogInfo();
	string toStringShort();
	string toStringFull();
};

class Log {
private:
	static Log* _instance;
	shared_ptr<LogAdapter> _adapter;
	bool _enabled = true;

	Log();

public:
	static int TYPE;
	static const int TYPE_SHORT = 1;
	static const int TYPE_FULL = 2;

	static Log& instance();
	static void log(LogInfo& info);
	static void log(Loggable& object);
	static void log(string& mes);

	static string time();

	void setAdapter(shared_ptr<LogAdapter> adapter);
};
#pragma once

#include <string>
#include <list>
#include <iostream>


using std::string;
using std::list;
using std::ostream;
using std::pair;

class LogInfo {
public:
	string name = "";
	list<pair<const string, const string>> params;

	LogInfo();
	LogInfo(const LogInfo& other);
	LogInfo(LogInfo&& other);

	void pushParam(const string& name, const string& value);
	void pushParam(const string&& name, const string&& value);

	void clear();

	LogInfo& operator=(const LogInfo& other);
	LogInfo& operator=(LogInfo&& other);

	friend ostream& operator<<(ostream& os, const LogInfo& info);
};
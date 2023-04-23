#include <memory>

#include <GAME/log/LogInfo.hpp>
#include <GAME/log/Log.hpp>


using std::move;

LogInfo::LogInfo() {}

LogInfo::LogInfo(const LogInfo& other) {
	name = other.name;
	params = other.params;
}

LogInfo::LogInfo(LogInfo&& other) {
	name = move(other.name);
	params = move(other.params);
}

LogInfo& LogInfo::operator=(const LogInfo& other) {
	*this = LogInfo(other);
	return *this;
}

LogInfo& LogInfo::operator=(LogInfo&& other) {
	name = move(other.name);
	params = move(other.params);
	return *this;
}

ostream& operator<<(ostream& os, const LogInfo& info) {
	os << info.name;

	if (Log::TYPE == Log::TYPE_SHORT)
		return os;

	os << "{";

	bool isFirst = true;
	for (pair<string, string> param : info.params) {
		if (!isFirst) {
			os << ", ";
		}

		isFirst = false;
		os << param.first << ": " << param.second;
	}

	os << "}";
	Log::instance();
	return os;
}

void LogInfo::clear() {
	name = "";
	params.clear();
}

void LogInfo::pushParam(const string& name, const string& value) {
	params.push_back(pair<string, string>(name, value));
}

void LogInfo::pushParam(const string&& name, const string&& value) {
	params.push_back(pair<string, string>(name, value));
}
#include <GAME/log/Log.hpp>
#include <GAME/log/ConsoleLogAdapter.hpp>
#include <GAME/log/LogInfo.hpp>

#include <ctime>
#include <iostream>
#include <sstream>

int Log::TYPE = Log::TYPE_FULL;

Log* Log::_instance = nullptr;


LogInfo& Loggable::makeLogInfo() {
	_logInfo.clear();
	fillLogInfo(_logInfo);
	return _logInfo;
}

string Loggable::toStringShort() {
	if (_logInfo.name == "")
		fillLogInfo(_logInfo);

	return _logInfo.name;
}

string Loggable::toStringFull() {
	fillLogInfo(_logInfo);
	std::ostringstream stream;
	stream << _logInfo;
	return stream.str();
}

Log& Log::instance() {
	if (_instance == nullptr)
		_instance = new Log();

	return *_instance;
}

Log::Log() : _adapter(shared_ptr<LogAdapter>(new ConsoleLogAdapter())) {

}

void Log::log(const string& mes) {
	if (!instance()._enabled)
		return;

	auto adapter = instance()._adapter;
	adapter->open();
	adapter->ostream() << time() << ": ";
	adapter->ostream() << mes;
	adapter->ostream() << std::endl;
	adapter->close();
}

void Log::log(Loggable& object) {
	if (!instance()._enabled)
		return;

	const LogInfo& info = object.makeLogInfo();

	auto adapter = instance()._adapter;
	adapter->open();
	adapter->ostream() << time() << ": ";
	adapter->ostream() << info;
	adapter->ostream() << std::endl;
	adapter->close();
}

void Log::log(LogInfo& info) {
	if (!instance()._enabled)
		return;

	auto adapter = instance()._adapter;
	adapter->open();
	adapter->ostream() << time() << ": ";
	adapter->ostream() << info;
	adapter->ostream() << std::endl;
	adapter->close();
}

void Log::setAdapter(shared_ptr<LogAdapter> adapter) {
	_adapter.swap(adapter);
}

string Log::time() {
	std::time_t t = std::time(nullptr);
	char mbstr[100];
	struct tm timeinfo;
	localtime_s(&timeinfo, &t);

	if (!std::strftime(mbstr, sizeof(mbstr), "%A %c", &timeinfo)) {
		return string();
	}

	return string(mbstr);
}
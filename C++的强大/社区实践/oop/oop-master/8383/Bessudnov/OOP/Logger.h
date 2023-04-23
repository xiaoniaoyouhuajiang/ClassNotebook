#pragma once
#include <string>
#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Interfaces.h"


class GameBase;
class UnitParent;

enum LoggerType {File, Console, Nothing};

class LogEntry {
private:
	std::string messageEntry;
public:

	LogEntry(std::string mes) : messageEntry(mes) {
	}

	friend std::ostream& operator<<(std::ostream &os, const LogEntry& logEntry) {
		os << logEntry.messageEntry << std::endl;
		return os;
	}
};

class Logger : public ILogger {
private:
	std::ofstream outputLogFile;
	Logger();
	LoggerType type;
	static Logger *logger;
public:
	~Logger();

	static Logger *getInstance();

	void setType(LoggerType type) {
		this->type = type;
	}
	void logEvent(LogEntry *entry);
	void printHistory(std::queue<LogEntry*> logsHistory);
};



class LoggerProxy : public ILogger {
private:
	std::queue<LogEntry*> logsHistoryQueue;
	LoggerType loggerType;
	Logger *logger;
public:
	LoggerProxy();
	~LoggerProxy() = default;

	void logEvent(LogEntry *entry);

	LoggerType getType() {
		return loggerType;
	}

	std::queue<LogEntry*> getLogHistory() {
		return logsHistoryQueue;
	}
};

class GameUnitAdapter : public LoggerProxy {
private:
	UnitParent *unit;
public:
	GameUnitAdapter(UnitParent *unit) : unit(unit) {
	}

	void logUnitSpawn();
	void logUnitMove();
	void logUnitDestroyed();
	void logUnitRecieveDamage(int damage);
};

class GameBaseAdapter : public LoggerProxy {
private:
	GameBase *base;
public:
	GameBaseAdapter(GameBase *base) : base(base) {
	}
	void logBaseSpawn();
	void logBaseSpawnUnit(UnitParent *spawnedUnit);

};

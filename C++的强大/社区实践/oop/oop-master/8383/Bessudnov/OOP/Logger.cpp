#include "pch.h"
#include "Logger.h"
#include "GameBases.h"
#include "UnitParent.h"
#include "MyException.h"

Logger::Logger() {
	try {
		outputLogFile.open("GameLog.txt", std::ofstream::out);
		if (!outputLogFile.is_open()) {
			throw FileException("Failed to load file.", "GameLog.txt", outputLogFile.rdstate());
		}
	} catch (FileException &exception) {
		std::cerr << exception.getMes() << std::endl;
	}
	
}


Logger::~Logger() {
	outputLogFile.close();
}

Logger *Logger::logger = nullptr;

Logger * Logger::getInstance() {
	if (logger == nullptr) {
		logger = new Logger();
	}

	return logger;
}

void Logger::logEvent(LogEntry *entry) {
	try {
		if (type = LoggerType::File) {
			if (!outputLogFile.is_open()) {
				throw FileException("File is not opened", "GameLog.txt", outputLogFile.rdstate());
			}
			outputLogFile << *entry;
		}
		if (type = LoggerType::Console) {
			std::cout << *entry;
		}
	} catch (FileException &exception) {
		std::cerr << exception.getMes() << std::endl;
	}
}

void Logger::printHistory(std::queue<LogEntry*> logsHistory) {
	while (!logsHistory.empty()) {
		std::cout << *logsHistory.front();
		logsHistory.pop();
	}
}


LoggerProxy::LoggerProxy() {
	logger = Logger::getInstance();
	loggerType = LoggerType::Console;
}

void LoggerProxy::logEvent(LogEntry *entry) {
	logsHistoryQueue.push(entry);
	if (logsHistoryQueue.size() > 10) {
		logsHistoryQueue.pop();
	}
	switch (loggerType) {
	case LoggerType::File:
		logger->setType(LoggerType::File);
		logger->logEvent(entry);
		break;
	case LoggerType::Console:
		logger->setType(LoggerType::Console);
		logger->logEvent(entry);
		logger->printHistory(logsHistoryQueue);
		break;
	case LoggerType::Nothing:
		break;
	}
}

void GameBaseAdapter::logBaseSpawn() {
	std::string logInfo;
	std::stringstream ss;

	ss << "Base: " << base->type << " spawned at " <<  base->location << std::endl;
	logInfo = ss.str();

	logEvent(new LogEntry(logInfo));
}

void GameBaseAdapter::logBaseSpawnUnit(UnitParent *spawnedUnit) {
	std::string logInfo;
	std::stringstream ss;

	ss << "Unit: " << spawnedUnit->unitProps.type << " spawned by base: " << base->type << std::endl;
	logInfo = ss.str();

	logEvent(new LogEntry(logInfo));
}

void GameUnitAdapter::logUnitSpawn() {
	std::string logInfo;
	std::stringstream ss;

	ss << "Unit: " << unit->unitProps.type << " spawned at " << unit->unitProps.location << std::endl;
	logInfo = ss.str();

	logEvent(new LogEntry(logInfo));
}

void GameUnitAdapter::logUnitMove() {
	std::string logInfo;
	std::stringstream ss;

	ss << "Unit: " << unit->unitProps.type << " moved to " << unit->unitProps.location << std::endl;
	logInfo = ss.str();

	logEvent(new LogEntry(logInfo));
}

void GameUnitAdapter::logUnitDestroyed() {
	std::string logInfo;
	std::stringstream ss;

	ss << "Unit: " << unit->unitProps.type << " recieved damage and dead. Destroying Unit... " << std::endl;
	logInfo = ss.str();

	logEvent(new LogEntry(logInfo));
}

void GameUnitAdapter::logUnitRecieveDamage(int damage) {
	std::string logInfo;
	std::stringstream ss;

	ss << "Unit: " << unit->unitProps.type << " recived damage:  " << damage << std::endl;
	logInfo = ss.str();

	logEvent(new LogEntry(logInfo));
}

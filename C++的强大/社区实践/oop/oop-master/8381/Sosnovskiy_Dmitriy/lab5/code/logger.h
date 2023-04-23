#pragma once
#include <QString>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <ctime>
#include "logdata.h"

enum LoggingType { TERMINAL_LOGGING, FILE_LOGGING, NO_LOGGING };

class ILogger{
public:
    virtual ~ILogger() = default;
    virtual void printLog(LogData* logData) = 0;
};

class TerminalLogger : public ILogger{
public:
    virtual void printLog(LogData* logData) override {
        logData->setFormat(FULL_INFO);
        std::cout << logData << "\n";
    }

};

class TerminalLoggerAdapter : public TerminalLogger {
public:
    virtual void printLog(LogData* logData)
    {
        logData->setFormat(ACTIONS_ONLY);
        std::cout << logData << "\n";
    }

};

class FileLogger : public ILogger {
protected:
    QFile file;
public:

    FileLogger()
    {
        file.setFileName("logs.txt");
    }

    virtual ~FileLogger() override
    {
    }

    virtual void printLog(LogData* logData) override {
        file.open(QIODevice::Append);
        logData->setFormat(FULL_INFO);
        QTextStream stream(&file);
        stream << logData << "\n";
        file.close();
    }
};

class FileLoggerAdapter : public FileLogger{
public:
    FileLoggerAdapter()
    {
        file.setFileName("logs.txt");
    }

    ~FileLoggerAdapter()
    {    }

    virtual void printLog(LogData* logData) {
        file.open(QIODevice::Append);
        logData->setFormat(ACTIONS_ONLY);
        QTextStream stream(&file);
        stream << logData << "\n";
        file.close();
    }
};

class ProxyLogger : public ILogger{
private:
    ILogger* logger;
    LoggingType type;
    LogFormatType format;
public:
    ProxyLogger(LoggingType type, LogFormatType format){
        if(format == FULL_INFO)
        {
            switch (type) {
                case TERMINAL_LOGGING:
                    logger = new TerminalLogger();
                    break;
                case FILE_LOGGING:
                    logger = new FileLogger();
                    break;
                default:
                    logger = nullptr;
                    break;
            }
        }
        else {
            switch (type) {
                case TERMINAL_LOGGING:
                    logger = new TerminalLoggerAdapter();
                    break;
                case FILE_LOGGING:
                    logger = new FileLoggerAdapter();
                    break;
                default:
                    logger = nullptr;
                    break;
            }
        }
    }

    ~ProxyLogger()
    {
        if(logger) delete logger;
    }

    void printLog(LogData* logData) override {
        if(logger) logger->printLog(logData);
    }
};

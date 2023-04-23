#pragma once
#include <string>
#include <fstream>
#include <iostream>

class Logger {
public:
    virtual void log() = 0;
    std::string getBuffer();
    void appendBuffer(std::string newMessage);
    void cleanBuffer();
    virtual ~Logger() = default;
protected:
    std::string buffer = std::string("");
};

class FileLogger : public Logger {
public:
    FileLogger();
    virtual ~FileLogger();
    void log();
private:
    std::string path = "log.text";
    std::ofstream file;
};

class TerminalLogger : public Logger {
public:
    TerminalLogger() = default;
    virtual ~TerminalLogger() = default;
    void log();
}; 
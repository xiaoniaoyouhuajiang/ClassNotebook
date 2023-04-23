#ifndef LABOOP_LOGGER_HPP
#define LABOOP_LOGGER_HPP

#include <string>
#include <iostream>

enum LoggerType {NO_LOG, FILE_LOG, TERMINAL_LOG};

class Logger {
public:
    ~Logger() = default;
    virtual void print() = 0;
    virtual void setLog(std::string logString) = 0;
    virtual void addLog(std::string logString) = 0;
    virtual void setFormat(int format) = 0;
    virtual int getFormat() = 0;
};


#endif //LABOOP_LOGGER_HPP

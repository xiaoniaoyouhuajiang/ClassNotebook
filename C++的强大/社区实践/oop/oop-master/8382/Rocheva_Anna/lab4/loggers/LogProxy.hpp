#ifndef LABOOP_LOGPROXY_HPP
#define LABOOP_LOGPROXY_HPP

#include "NoLogger.hpp"
#include "FileLogger.hpp"
#include "TerminalLogger.hpp"

class LogProxy : public Logger{
public:
    explicit LogProxy(LoggerType loggerType);
    ~LogProxy() = default;
    void print() final {if (logger) logger->print();};
    void setLog(std::string logString) final {logger->setLog(logString);};
    void addLog(std::string logString) final {logger->addLog(logString);};
    void setFormat(int format) final {logger->setFormat(format);};
    int getFormat() final { return logger->getFormat();};
private:
    Logger *logger;
};


#endif //LABOOP_LOGPROXY_HPP

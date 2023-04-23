#ifndef PROXY_H
#define PROXY_H

#include "enums.h"
#include "logger.h"
#include "terminalloger.h"
#include "filelogger.h"
class ProxyLogger : public Logger
{
public:
    ProxyLogger(LogPlace logPlace);
    ~ProxyLogger();
    bool isActive();
    void prinLog(string);
    void print();
    string getLog() const;
    void setLog(string &);
private:
    Logger* logger;

};

#endif // PROXY_H

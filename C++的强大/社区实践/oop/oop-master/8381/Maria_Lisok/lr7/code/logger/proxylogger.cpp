#include "proxylogger.h"


ProxyLogger::ProxyLogger(LogPlace logPlace)
{
    if(logPlace == NOLOG){
        logger = nullptr;
    }else if(logPlace == TOTERMINAL){
        logger = new TerminalLogger();
    }else if(logPlace == TOFILE){
        logger = new FileLogger(FILENAME);
    }
}

ProxyLogger::~ProxyLogger()
{
    if(logger){
        delete logger;
        logger = nullptr;
    }

}

bool ProxyLogger::isActive()
{
    if(logger)
        return logger->isActive();
    else
        return false;
}

void ProxyLogger::prinLog(string val)
{
    if(logger)
        logger->prinLog(val);
}

void ProxyLogger::print()
{
    if(logger)
        logger->print();
}

string ProxyLogger::getLog() const
{
    if(logger)
        logger->getLog();
    return "no logger";
}

void ProxyLogger::setLog(string & val)
{
    if(logger)
        logger->setLog(val);
}

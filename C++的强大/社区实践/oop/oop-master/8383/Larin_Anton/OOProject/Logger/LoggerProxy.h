//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_LOGGERPROXY_H
#define OOPROJECT_LOGGERPROXY_H

#include <memory>

#include "AbstractLogger.h"
class LoggerProxy:public AbstractLogger{

private:
    std::shared_ptr<AbstractLogger> abstractLogger;
public:
    LoggerProxy(const std::shared_ptr<AbstractLogger> &abstractLogger) : abstractLogger(abstractLogger) {}

    LoggerProxy() {}

    void setAbstractLogger(const std::shared_ptr<AbstractLogger> &abstractLogger) {
        LoggerProxy::abstractLogger = abstractLogger;
    }

public:
    void log(std::string str) override {
        abstractLogger->log(str);
    }
};


#endif //OOPROJECT_LOGGERPROXY_H

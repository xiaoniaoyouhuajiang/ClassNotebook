#ifndef LOGGER_H
#define LOGGER_H
#include "save.h"

CacheSave* cacheObj = 0;
SimpleSave* simpleObj = 0;

class Logger{
private:
    static Logger* log_instance;
    Logger(){}
    Logger(const Logger&);
    Logger& operator = (Logger&);

public:
    static Logger* getInstance(){
        if (!log_instance){
            qInfo() << "created logger class";
            log_instance = new Logger();
        }
        return log_instance;
    }

    CacheSave* getCache(){
        if (!cacheObj){
                cacheObj = new CacheSave();
        }
        return cacheObj;
    }

    SimpleSave* getSimple(){
        if (!simpleObj){
            simpleObj = new SimpleSave();
        }
        return simpleObj;
    }

    void printInfo(QString msg){
        qInfo() << msg;
    }

    void printDebug(QString msg){
        qDebug() << msg;
    }

    void printWarning(QString msg){
        qWarning() << msg;
    }

    void printCritical(QString msg){
        qCritical() << msg;
    }
};

Logger* Logger::log_instance = 0;

#endif // LOGGER_H


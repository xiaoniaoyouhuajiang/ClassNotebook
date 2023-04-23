//
// Created by shenk on 24.03.2020.
//

#ifndef UNTITLED13_LOGPROXY_H
#define UNTITLED13_LOGPROXY_H

#include "Loggers/NoLogger.h"
#include "Formats/NoFormat.h"

#include <string>
#include <iostream>

class LogProxy {

private:

    Logger *logger;
    LogFormat *logFormat;
    bool isFirstInLine = true;

    void log(std::string s){
        if (isFirstInLine) {
            std::string formatted = logFormat->getFormatted(s);
            logger->log(formatted);
            isFirstInLine = false;
        } else{
            logger->log(s);
        }
    }

public:

    LogProxy(): logger(new NoLogger()), logFormat(new NoFormat()){}
    ~LogProxy(){
        delete logger;
        delete logFormat;
    }

    friend LogProxy& operator<< (LogProxy &logger, const std::string &s){
        logger.log(s);
        return logger;
    }

    friend LogProxy& operator<< (LogProxy &logger, const int i){
        logger.log(std::to_string(i));
        return logger;
    }

    friend LogProxy& operator<< (LogProxy &logger, const game::Logend &l){
        logger.log("\n");
        logger.isFirstInLine = true;
        return logger;
    }

    void setLogger(Logger *logger1){

        delete logger;
        logger = logger1;
    }

    void setLogFormat(LogFormat *logFormat1){

        delete logFormat;
        logFormat = logFormat1;

    }

};



#endif //UNTITLED13_LOGPROXY_H

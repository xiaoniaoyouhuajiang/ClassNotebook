//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_ABSTRACTLOGGER_H
#define OOPROJECT_ABSTRACTLOGGER_H

#include <memory>
#include <string>

class AbstractLogger {
public:
    virtual void log(std::string str)=0;



    virtual AbstractLogger&operator<<(std::string str){
        log(str);
        return *this;
    }


    friend std::shared_ptr<AbstractLogger>& operator<<(std::shared_ptr<AbstractLogger>& logger,std::string str){
        logger->operator<<(str);
        return logger;
    }



};


#endif //OOPROJECT_ABSTRACTLOGGER_H

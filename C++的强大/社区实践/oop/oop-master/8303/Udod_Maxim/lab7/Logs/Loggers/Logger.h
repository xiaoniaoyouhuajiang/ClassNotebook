//
// Created by shenk on 24.03.2020.
//

#ifndef UNTITLED13_LOGGER_H
#define UNTITLED13_LOGGER_H

#include <string>
#include "../Logend.h"

class Logger {

public:

    virtual void log(std::string &s)=0;
    virtual void log(game::Logend &l){}
    virtual ~Logger(){}

};


#endif //UNTITLED13_LOGGER_H

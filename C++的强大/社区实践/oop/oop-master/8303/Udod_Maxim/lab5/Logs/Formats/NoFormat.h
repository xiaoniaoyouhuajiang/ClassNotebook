//
// Created by shenk on 24.03.2020.
//

#ifndef UNTITLED13_NOFORMAT_H
#define UNTITLED13_NOFORMAT_H


#include "LogFormat.h"

class NoFormat: public LogFormat {

    std::string getFormatted(std::string &notFormatted) override{
        return notFormatted;
    }

};


#endif //UNTITLED13_NOFORMAT_H

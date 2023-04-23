//
// Created by shenk on 24.03.2020.
//

#ifndef UNTITLED13_LOGFORMAT_H
#define UNTITLED13_LOGFORMAT_H

#include <string>

class LogFormat {

public:

    virtual std::string getFormatted(std::string &notFormatted)=0;

};


#endif //UNTITLED13_LOGFORMAT_H

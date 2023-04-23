//
// Created by shenk on 24.03.2020.
//

#ifndef UNTITLED13_TIMEFORMAT_H
#define UNTITLED13_TIMEFORMAT_H

#include <ctime>

#include "LogFormat.h"

class TimeFormat: public LogFormat {

    std::string getFormatted(std::string &notFormatted) override{

        time_t rawtime;
        struct tm * timeinfo;
        char buffer [80];                                // строка, в которой будет храниться текущее время

        time ( &rawtime );                               // текущая дата в секундах
        timeinfo = localtime ( &rawtime );               // текущее локальное время, представленное в структуре

        strftime (buffer,80," [%c] ",timeinfo); // форматируем строку времени

        return buffer+notFormatted;

    }

};


#endif //UNTITLED13_TIMEFORMAT_H

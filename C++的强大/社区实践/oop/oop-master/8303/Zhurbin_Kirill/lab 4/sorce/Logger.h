#ifndef OOP1_LOGGER_H
#define OOP1_LOGGER_H

#include <string>
#include <iostream>
#include "LoggerProtected.h"
#include "File.h"

class Logger: LoggerProtected{

public:
    Logger(){

    }

protected:
    void print(std::string log, bool writeAble, bool filewriteAble){
        if (writeAble){
            if (filewriteAble){
                printToFile(log);
            }

            else{
                printToConsole(log);
            }
        }
    }
};

#endif //OOP1_LOGGER_H

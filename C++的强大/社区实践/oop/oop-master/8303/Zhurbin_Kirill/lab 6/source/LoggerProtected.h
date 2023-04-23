#ifndef OOP1_LOGGERPROTECTED_H
#define OOP1_LOGGERPROTECTED_H

#include <string>
#include <iostream>
#include "File.h"

class LoggerProtected{
    FileWrite* file;
protected:

    void printToConsole(std::string message){
        std::cout << "log: " << message << std::endl;
    }

    void printToFile(std::string message){
        file = new FileWrite("Log.txt", "log");
        file->write("log:" + message);
        delete file;
    };
};

#endif //OOP1_LOGGERPROTECTED_H

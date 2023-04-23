//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_FILELOGGERADAPTER_H
#define OOPROJECT_FILELOGGERADAPTER_H

#include "AbstractLogger.h"


#include "FileLogger.h"

class FileLoggerAdapter:public FileLogger,public AbstractLogger{
public:
    FileLoggerAdapter(const std::string &fileName) : FileLogger(fileName) {}

    void log(std::string str) override {
        logToFile(str);
    }
};

#endif //OOPROJECT_FILELOGGERADAPTER_H

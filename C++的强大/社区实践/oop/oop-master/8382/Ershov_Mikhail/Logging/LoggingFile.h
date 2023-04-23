#pragma once

#include "Logger.h"
#include <fstream>

using namespace std;

class LoggingFile : public Logger {
public:
    LoggingFile(string file);
    ~LoggingFile();
    void log(const string& str);

private:
    ofstream outFile;
};
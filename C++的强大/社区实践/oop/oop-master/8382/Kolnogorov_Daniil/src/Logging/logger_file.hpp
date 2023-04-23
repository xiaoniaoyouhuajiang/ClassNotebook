#pragma once

#include "logger.hpp"
#include <fstream>

using namespace std;

class LoggerFile : public Logger {
public:
    LoggerFile(string file) { file_stream.open(file, ofstream::app); }
    ~LoggerFile() { file_stream.close(); }

    void log(const string& str) {
        file_stream << str;
        file_stream.flush();
    }

private:
    ofstream file_stream;
};

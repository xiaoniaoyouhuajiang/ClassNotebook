#include <iostream>
#include <fstream>
#include <sstream>
#include "writer.h"
#include <chrono>
#include <ctime>
#ifndef LOGWRITER_H
#define LOGWRITER_H

class LogWriter {
private:
    std::unique_ptr<IWriter> writer= nullptr;
    static LogWriter* instance;
    LogWriter(int mode);
public:
    static const int NO_LOG = 0;
    static const int BUFFERED_LOG = 1;
    static const int REALTIME_LOG = 2;
    static LogWriter& getInstance();

    void changeMode(int mode);

    void log(std::string message);

    virtual ~LogWriter();

    LogWriter(LogWriter const&) = delete;
    void operator=(LogWriter const&) = delete;
};

#endif // LOGWRITER_H

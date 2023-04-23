//
// Created by smokfyz on 19.05.19.
//

#ifndef XGAME_LOGGER_H
#define XGAME_LOGGER_H

#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;


class LoggerInterface {

public:
    virtual ~LoggerInterface() = default;

    virtual void write(string) = 0;
    virtual string readline() = 0;
    virtual string read() = 0;
};


class Logger : public LoggerInterface {
    Logger(unsigned = 20);

    unique_ptr<LoggerInterface> logger;

    bool logging;
    bool cached;
    unsigned cache_size;
    vector<string> cache;

public:
    Logger(Logger const&)          = delete;
    void operator=(Logger const&)  = delete;

    static Logger &getLogger();

    void setLogger(unique_ptr<LoggerInterface>&&);

    void write(string) override;
    string readline() override;
    string read() override;

    void cachedMode(bool);
    void loggingMode(bool);

    bool getCached();
    bool getLogging();
};


class FileLogger : public LoggerInterface {
    ofstream olog_file;
    ifstream ilog_file;

public:
    explicit FileLogger(string = "log.txt");
    ~FileLogger() override;

    void write(string) override;
    string readline() override;
    string read() override;

};
#endif //XGAME_LOGGER_H

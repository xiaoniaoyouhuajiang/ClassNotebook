#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "logger.h"
#include <fstream>


class FileLogger : public Logger
{
public:
    FileLogger(string fileName);
    ~FileLogger();
    bool isActive();
    void prinLog(string);
    void print();
    string getLog() const;
    void setLog(string &);
    friend ostream& operator<<(std::ostream& os, const Logger& l);
private:
    string log;
    ofstream file;
};

#endif // FILELOGGER_H

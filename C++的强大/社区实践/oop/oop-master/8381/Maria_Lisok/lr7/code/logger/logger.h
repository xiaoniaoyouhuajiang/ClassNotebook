#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
using namespace std;
class Logger{
public:
    virtual bool isActive()=0;
    virtual void prinLog(string)=0;
    virtual void print()=0;
    virtual string getLog() const=0;
    virtual void setLog(string&)=0;
    virtual ~Logger()=default;
};
#endif // LOGGER_H

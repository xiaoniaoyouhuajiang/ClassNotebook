#ifndef TERMINALLOGER_H
#define TERMINALLOGER_H

#include "logger.h"



class TerminalLogger : public Logger
{
public:
    TerminalLogger();
    ~TerminalLogger();
    bool isActive();
    void prinLog(string);
    void print();
    friend ostream& operator<<(ostream& os, const Logger& l);
    string getLog() const;
    void setLog(string&);
private:
    string log;

};

#endif // TERMINALLOGER_H

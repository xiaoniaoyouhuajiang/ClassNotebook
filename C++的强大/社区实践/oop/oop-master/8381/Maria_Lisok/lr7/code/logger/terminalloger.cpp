#include "terminalloger.h"

TerminalLogger::TerminalLogger()
{
    cout << "logger start" << endl;
}

TerminalLogger::~TerminalLogger()
{
    cout << "logger stopped" << endl;
}

bool TerminalLogger::isActive()
{
    return true;
}

void TerminalLogger::prinLog(string log)
{
    setLog(log);
    print();
}

void TerminalLogger::print()
{
   cout << *this << endl;
}

string TerminalLogger::getLog() const
{
    return log;
}

void TerminalLogger::setLog(string & log)
{
    this->log = log;
}


ostream& operator<<(ostream &ostr, const Logger &l)
{
    ostr << l.getLog();
    return ostr;
}

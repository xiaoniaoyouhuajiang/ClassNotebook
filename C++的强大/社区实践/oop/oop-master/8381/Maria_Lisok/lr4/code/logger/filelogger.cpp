#include "filelogger.h"

FileLogger::FileLogger(string fileName)
{
    file.open(fileName);
    if(!file.is_open())
        throw runtime_error("problem with opening file");
    file << "Logger start" << endl;
}

FileLogger::~FileLogger()
{
    file << "Logger stopped" << endl;
    file.close();
}

bool FileLogger::isActive()
{
    return true;
}

void FileLogger::prinLog(string value)
{
    setLog(value);
    print();
}

void FileLogger::print()
{
   file << *this << endl;
}

string FileLogger::getLog() const
{
    return log;
}

void FileLogger::setLog(string & log)
{
    this->log = log;
}


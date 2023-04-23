#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <sstream>
#include "adapter.h"
#include "Units/unit.h"
#include "file.h"

class LoggerProxy;

class Logger
{
    static void printLogFile(std::string&);
    static void printLogConsole(std::string&);
    static bool fileIsOpen;
    static File* file;

public:
    Logger();

    friend class LoggerProxy;
};

#endif // LOGGER_H

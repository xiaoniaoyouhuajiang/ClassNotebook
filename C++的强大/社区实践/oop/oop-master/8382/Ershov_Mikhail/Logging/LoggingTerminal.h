#pragma once

#include "Logger.h"
#include <iostream>

using namespace std;

class LoggingTerminal : public Logger {
public:
    void log(const string& str);
};
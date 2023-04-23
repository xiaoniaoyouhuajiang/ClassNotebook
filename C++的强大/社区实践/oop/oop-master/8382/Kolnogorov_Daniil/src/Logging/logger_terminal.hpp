#pragma once

#include "logger.hpp"
#include <iostream>

using namespace std;

class LoggerTerminal : public Logger {
public:
    void log(const string& str) { cout << str; }
};

#pragma once

#include "formatter.hpp"
#include <ctime>
#include <string>

using namespace std;

class FormatterTime : public LogFormatter {
public:
    string format(string str) override {
        time_t rawtime;
        char buffer[80];
        time(&rawtime);
        struct tm* timeinfo = localtime(&rawtime);
        strftime(buffer, sizeof(buffer), "[%H:%M:%S] ", timeinfo);
        return buffer + str;
    }
};

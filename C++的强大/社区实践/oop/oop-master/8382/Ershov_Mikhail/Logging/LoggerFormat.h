#pragma once

#include <string>
#include <ctime>

using namespace std;

class LogFormatter {
public:
    virtual ~LogFormatter() = default;
    virtual string format(string str) = 0;
};

//-----------------------------------------------------

class FormatterTime : public LogFormatter {
public:
    string format(string str) override;
};

//-----------------------------------------------------

class FormatterEmpty : public LogFormatter {
public:
    string format(string str) override;
};

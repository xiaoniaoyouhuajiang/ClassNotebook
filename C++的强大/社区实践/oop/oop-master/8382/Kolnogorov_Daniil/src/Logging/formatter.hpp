#pragma once

#include <string>

using namespace std;

class LogFormatter {
public:
    virtual ~LogFormatter() = default;
    virtual string format(string str) = 0;
};

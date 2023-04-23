#pragma once

#include <string>

class Logger {
public:
    struct Endl {};

    virtual void log(const std::string& str) = 0;
    virtual ~Logger() = default;
};
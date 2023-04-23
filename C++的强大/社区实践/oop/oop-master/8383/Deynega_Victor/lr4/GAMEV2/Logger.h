#pragma once
#include <string>
#include "File.h"

class Logger {
public:
    bool writeToFile, loggerOn;
    File* ptr;
    explicit Logger();
    void print(std::string);
    friend class ProxyLogger;
};
#pragma once

#include "Logger.h"
#include <string>

class NoLogging : public Logger {
public:
    ~NoLogging() override {}
    void log(const std::string&) override {
        return;
    }
};
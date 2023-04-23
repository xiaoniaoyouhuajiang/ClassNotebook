#pragma once

#include "logger.hpp"
#include <string>

class LoggerEmpty : public Logger {
public:
    ~LoggerEmpty() override {}
    void log(const std::string&) override {
        return;
    }
};

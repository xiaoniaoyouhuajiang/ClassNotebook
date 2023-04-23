#pragma once

#include "formatter_empty.hpp"
#include "logger.hpp"
#include "logger_empty.hpp"
#include <string>

using namespace std;

class LoggerProxy {
public:
    LoggerProxy()
        : logger(new LoggerEmpty()), formatter(new FormatterEmpty()) {}
    ~LoggerProxy() {
        delete logger;
        delete formatter;
    }

    void set_logger(Logger* logger) {
        delete this->logger;
        this->logger = logger;
    };

    void enable_logging() { logging_enabled = true; }
    void disable_logging() { logging_enabled = false; }

    void set_formatter(LogFormatter* formatter) {
        delete this->formatter;
        this->formatter = formatter;
    };

    friend LoggerProxy& operator<<(LoggerProxy& logger, const string& str) {
        if (logger.logging_enabled) {
            logger.log(str);
        }
        return logger;
    }

    friend LoggerProxy& operator<<(LoggerProxy& logger, const unsigned value) {
        if (logger.logging_enabled) {
            logger.log(to_string(value));
        }
        return logger;
    }

    friend LoggerProxy& operator<<(LoggerProxy& logger, const Logger::Endl&) {
        if (logger.logging_enabled) {
            logger << "\n";
            logger.print_formatted = true;
        }
        return logger;
    }

private:
    Logger* logger;
    LogFormatter* formatter;
    bool print_formatted = true;
    bool logging_enabled = true;

    void log(const string& str) {
        if (print_formatted) {
            logger->log(formatter->format(str));
            print_formatted = false;
        } else {
            logger->log(str);
        }
    }
};

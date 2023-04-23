#include "LoggerProxy.h"

LoggerProxy::LoggerProxy() : logger(new NoLogging()), formatter(new FormatterEmpty()) {

}

LoggerProxy::~LoggerProxy() {
    delete logger;
    delete formatter;
}

void LoggerProxy::setLogger(Logger* logger) {
    delete this->logger;
    this->logger = logger;
}

void LoggerProxy::setFormat(LogFormatter* formatter) {
    delete this->formatter;
    this->formatter = formatter;
}

LoggerProxy& operator<<(LoggerProxy& logger, const string& str) {
    logger.log(str);
    return logger;
}

LoggerProxy& operator<<(LoggerProxy& logger, const unsigned value) {
    logger.log(to_string(value));
    return logger;
}

LoggerProxy& operator<<(LoggerProxy& logger, const Logger::Endl&) {
    logger << "\n";
    logger.printFormatted = true;
    return logger;
}

void LoggerProxy::log(const string& str) {
    if (printFormatted) {
        logger->log(formatter->format(str));
        printFormatted = false;
    }
    else {
        logger->log(str);
    }
}

#ifndef LAB2_OOP_LOGPROXY_H
#define LAB2_OOP_LOGPROXY_H

#include "../Logging/Loggers/NoLogger.h"
#include "../Logging/Formats/NoFormat.h"

#include <string>
#include <iostream>

class LogProxy {
 private:
  Logger *logger;
  LogFormat *logFormat;
  bool isOnFirstInLine = true;

  void log(std::string s) {
    if (isOnFirstInLine) {
      std::string formatted = logFormat->getFormatted(s);
      logger->log(formatted);
      isOnFirstInLine = false;
    } else {
      logger->log(s);
    }
  }

 public:
  LogProxy() : logger(new NoLogger()), logFormat(new NoFormat()) {}

  ~LogProxy() {
    delete logger;
    delete logFormat;
  }

  friend LogProxy &operator<<(LogProxy &logger, const std::string &s) {
    logger.log(s);
    return logger;
  }

  friend LogProxy &operator<<(LogProxy &logger, const int i) {
    logger.log(std::to_string(i));
    return logger;
  }

  friend LogProxy &operator<<(LogProxy &logger, const unsigned long long i) {
    logger.log(std::to_string(i));
    return logger;
  }

  friend LogProxy &operator<<(LogProxy &logger, const unsigned long i) {
    logger.log(std::to_string(i));
    return logger;
  }

  friend LogProxy &operator<<(LogProxy &logger, const game::Logend &l) {
    logger.log("\n");
    logger.isOnFirstInLine = true;
    return logger;
  }

  void setLogger(Logger *newLogger) {
    delete logger;
    logger = newLogger;
  }

  void setLogFormat(LogFormat *newLogFormat) {
    delete logFormat;
    logFormat = newLogFormat;
  }
};

#endif //LAB2_OOP_LOGPROXY_H

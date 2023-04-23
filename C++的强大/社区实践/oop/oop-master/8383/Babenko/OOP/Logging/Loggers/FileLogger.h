#ifndef LAB2_OOP_FILELOGGER_H
#define LAB2_OOP_FILELOGGER_H

#include <fstream>
#include "Logger.h"

class FileLogger : public Logger {
 private:
  std::ofstream fileStream;

 public:
  explicit FileLogger(std::string filePath) : fileStream(filePath) {}

  ~FileLogger() override {
    fileStream.close();
  }

  void log(std::string &string) override {
    fileStream << string;
  }

  void log(game::Logend &logend) override {
    fileStream.flush();
  }
};

#endif //LAB2_OOP_FILELOGGER_H

#ifndef LAB2_OOP_TERMINALLOGGER_H
#define LAB2_OOP_TERMINALLOGGER_H

#include <iostream>
#include "Logger.h"

class TerminalLogger : public Logger {
 public:
  void log(std::string &s) override {
    std::cout << s;
  }
};

#endif //LAB2_OOP_TERMINALLOGGER_H

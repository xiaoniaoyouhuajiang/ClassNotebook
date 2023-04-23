#ifndef LAB2_OOP_NOLOGGER_H
#define LAB2_OOP_NOLOGGER_H

#include "Logger.h"

class NoLogger: public Logger {
 public:
  void log(std::string &s) override {}
};

#endif //LAB2_OOP_NOLOGGER_H

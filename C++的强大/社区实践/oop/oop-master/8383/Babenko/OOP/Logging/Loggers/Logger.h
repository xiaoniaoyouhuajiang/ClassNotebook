#ifndef LAB2_OOP_LOGGER_H
#define LAB2_OOP_LOGGER_H

#include <string>
#include "../Logend.h"

class Logger {
 public:
  virtual void log(std::string &string) = 0;
  virtual void log(game::Logend &logend) {}
  virtual ~Logger() {}
};

#endif //LAB2_OOP_LOGGER_H

#ifndef LAB2_OOP_REQUESTMEMENTO_H
#define LAB2_OOP_REQUESTMEMENTO_H

#include <string>
#include <fstream>
#include <utility>

class RequestMemento {
 private:
  std::string commandLine;

 public:
  RequestMemento(std::string commandLine) : commandLine(std::move(commandLine)) {}
  void saveToFile(std::ofstream &fileStream) const {
    fileStream << commandLine;
  }

  unsigned long int getHash(std::hash<std::string> &hashFunction) {
    return hashFunction(commandLine);
  }
};

#endif //LAB2_OOP_REQUESTMEMENTO_H

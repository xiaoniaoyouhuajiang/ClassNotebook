#ifndef LAB2_OOP_REQUEST_H
#define LAB2_OOP_REQUEST_H

#include <string>
#include <memory>
#include <sstream>

#include "../../GameField.h"
#include "../GameInfo.h"
#include "../Memento/RequestMemento.h"

class Request {
 public:
  virtual void execute(GameInfo &gameInfo) {
    game::log << "[Game] Wrong command! Try Again." << game::logend;
  }
  virtual RequestMemento *getMemento() const {
    return new RequestMemento("Wrong command\n");
  }
  virtual ~Request(){}
};

typedef std::unique_ptr<Request> RequestPtr;

class RequestHandler {
 protected:
  RequestHandler *next;

 public:
  virtual RequestPtr handle(std::vector<std::string> &cmd)=0;
  virtual bool canHandle(std::vector<std::string> &cmd)=0;
  void setNext(RequestHandler *requestHandler) {
    next = requestHandler;
  }
  virtual ~RequestHandler()= default;
};

#endif //LAB2_OOP_REQUEST_H

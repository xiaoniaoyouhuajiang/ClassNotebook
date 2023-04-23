#ifndef LAB2_OOP_MAINREQUESTINTERPRETER_H
#define LAB2_OOP_MAINREQUESTINTERPRETER_H

#include "Requests/Request.h"
#include "Requests/AttackRequest.h"
#include "Requests/CreateRequest.h"
#include "Requests/MoveRequest.h"
#include "Requests/ShowRequest.h"
#include "Requests/ExitRequest.h"
#include "Requests/NewRequest.h"
#include "Memento/SaveRequest.h"
#include "Memento/LoadRequest.h"

class MainRequestInterpreter {
 private:
  AttackRequestHandler *attackHandler;
  CreateRequestHandler *createHandler;
  MoveRequestHandler *moveHandler;
  ShowRequestHandler *showHandler;
  ExitRequestHandler *exitHandler;
  SaveRequestHandler *saveHandler;
  LoadRequestHandler *loadHandler;
  NewRequestHandler *newHandler;

 public:
  MainRequestInterpreter() {
    attackHandler = new AttackRequestHandler();
    createHandler = new CreateRequestHandler();
    moveHandler = new MoveRequestHandler();
    showHandler = new ShowRequestHandler();
    exitHandler = new ExitRequestHandler();
    saveHandler = new SaveRequestHandler();
    loadHandler = new LoadRequestHandler();
    newHandler = new NewRequestHandler();

    attackHandler->setNext(createHandler);
    createHandler->setNext(moveHandler);
    moveHandler->setNext(showHandler);
    showHandler->setNext(exitHandler);
    exitHandler->setNext(saveHandler);
    saveHandler->setNext(loadHandler);
    loadHandler->setNext(newHandler);
  }

  RequestPtr handle(std::string requestString) {
    std::vector<std::string> requestSplitted;
    std::stringstream stream(requestString);
    std::string requestWord;
    while (stream >> requestWord)
      requestSplitted.push_back(requestWord);

    return attackHandler->handle(requestSplitted);
  }

  ~MainRequestInterpreter() {
    delete attackHandler;
    delete createHandler;
    delete moveHandler;
    delete showHandler;
    delete exitHandler;
    delete saveHandler;
    delete loadHandler;
    delete newHandler;
  }
};

#endif //LAB2_OOP_MAINREQUESTINTERPRETER_H

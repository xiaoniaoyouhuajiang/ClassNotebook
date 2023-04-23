#ifndef LAB2_OOP_CREATEREQUEST_H
#define LAB2_OOP_CREATEREQUEST_H

#include "Request.h"
#include "CreateUnitRequest.h"
#include "CreateBaseRequest.h"

class CreateRequestHandler : public RequestHandler {
 public:
  bool canHandle(std::vector<std::string> &cmd) override {
    return cmd.size() > 1 && cmd[0] == "create";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override {
    if (canHandle(cmd)) {
      cmd.erase(cmd.begin());

      auto firstHandler = new CreateUnitRequestHandler();
      auto secondHandler = new CreateBaseRequestHandler();

      firstHandler->setNext(secondHandler);

      return firstHandler->handle(cmd);
    }

    if (next)
      return next->handle(cmd);
    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_CREATEREQUEST_H

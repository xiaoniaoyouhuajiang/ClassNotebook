#ifndef LAB2_OOP_ATTACKREQUEST_H
#define LAB2_OOP_ATTACKREQUEST_H

#include "Request.h"
#include "AttackUnitRequest.h"

class AttackRequestHandler : public RequestHandler {
 public:
  bool canHandle(std::vector<std::string> &cmd) override {
    return cmd.size() > 1 && cmd[0] == "attack";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override {
    if (canHandle(cmd)) {
      cmd.erase(cmd.begin());
      auto requestHandler = new AttackUnitRequestHandler();
      return requestHandler->handle(cmd);
    }

    if (next)
      return next->handle(cmd);
    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_ATTACKREQUEST_H

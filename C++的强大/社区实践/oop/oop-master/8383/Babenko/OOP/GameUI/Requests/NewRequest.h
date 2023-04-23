#ifndef LAB2_OOP_NEWREQUEST_H
#define LAB2_OOP_NEWREQUEST_H

#include "Request.h"
#include "NewGameRequest.h"
#include <memory>

class NewRequestHandler : public RequestHandler {
 public:
  bool canHandle(std::vector<std::string> &cmd) override {
    return cmd.size() > 1 && cmd[0] == "new";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override {
    if (canHandle(cmd)) {
      cmd.erase(cmd.begin());
      auto handler = new NewGameRequestHandler;

      return handler->handle(cmd);
    }

    if (next)
      return next->handle(cmd);

    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_NEWREQUEST_H

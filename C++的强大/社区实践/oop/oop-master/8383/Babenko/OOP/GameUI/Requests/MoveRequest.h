#ifndef LAB2_OOP_MOVEREQUEST_H
#define LAB2_OOP_MOVEREQUEST_H

#include "Request.h"
#include "MoveUnitRequest.h"

class MoveRequestHandler: public RequestHandler{
 public:
  bool canHandle(std::vector<std::string> &cmd) override {
    return cmd.size() > 1 && cmd[0] == "move";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override {
    if (canHandle(cmd)) {
      cmd.erase(cmd.begin());
      auto handler = new MoveUnitRequestHandler();
      return handler->handle(cmd);
    }

    if (next)
      return next->handle(cmd);
    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_MOVEREQUEST_H

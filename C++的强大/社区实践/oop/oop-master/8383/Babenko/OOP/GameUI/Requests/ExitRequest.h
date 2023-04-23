#ifndef LAB2_OOP_EXITREQUEST_H
#define LAB2_OOP_EXITREQUEST_H

#include "Request.h"

class ExitRequest: public Request{
  void execute(GameInfo &gameInfo) override {
    game::log << "[Game] Game finished" << game::logend;
    exit(0);
  }
};

class ExitRequestHandler: public RequestHandler{
 public:
  bool canHandle(std::vector<std::string> &cmd) override{
    return cmd.size() == 1 && cmd[0] == "exit";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override{
    if (canHandle(cmd)){
      cmd.erase(cmd.begin());
      return RequestPtr(new ExitRequest());
    }

    if (next)
      return next->handle(cmd);
    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_EXITREQUEST_H

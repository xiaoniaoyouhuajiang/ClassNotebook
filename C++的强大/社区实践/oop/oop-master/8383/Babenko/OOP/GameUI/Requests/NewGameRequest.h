#ifndef LAB2_OOP_NEWGAMEREQUEST_H
#define LAB2_OOP_NEWGAMEREQUEST_H

#include "Request.h"

class NewGameRequest: public Request {
 public:
  explicit NewGameRequest(){}

  void execute(GameInfo &gameInfo) override {
    gameInfo.createNewGame();
  }
};

class NewGameRequestHandler: public RequestHandler {
 public:
  bool canHandle(std::vector<std::string> &cmd) override {
    return cmd.size() == 1 && cmd[0] == "game";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override {
    if (canHandle(cmd)){
      return RequestPtr(new NewGameRequest());
    }

    if (next)
      return next->handle(cmd);
    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_NEWGAMEREQUEST_H

#ifndef LAB2_OOP_CREATEBASEREQUEST_H
#define LAB2_OOP_CREATEBASEREQUEST_H

#include "Request.h"
#include "../../FlyWeight/ArmorFlyWeight.h"
#include "../../Armor/BaseArmor.h"

class CreateBaseRequest : public Request {
 private:
  Point basePosition;

 public:
  explicit CreateBaseRequest(Point position) : basePosition(position) {}

  void execute(GameInfo &gameInfo) override {
    auto *base = new Base(100, *ArmorFlyWeight::getFlyWeight<BaseArmor>());
    if (gameInfo.setCurrentPlayerBase(base, basePosition)) {
      game::log << "[Game] Obtained base creation request" << game::logend;
      gameInfo.getField().addBase(base, basePosition);
    } else
      game::log << "[Game] This player already has base" << game::logend;
  }

  RequestMemento *getMemento() const override {
    std::stringstream stream;
    stream << "create base " << basePosition.x << " " << basePosition.y << std::endl;
    return new RequestMemento(stream.str());
  }
};

class CreateBaseRequestHandler : public RequestHandler {
 public:
  bool canHandle(std::vector<std::string> &cmd) override {
    return cmd.size() == 3 && cmd[0] == "base";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override {
    if (canHandle(cmd)) {
      int x = std::stoi(cmd[1]);
      int y = std::stoi(cmd[2]);
      Point basePosition(x, y);
      return RequestPtr(new CreateBaseRequest(basePosition));
    }

    if (next)
      return next->handle(cmd);
    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_CREATEBASEREQUEST_H

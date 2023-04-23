#ifndef LAB2_OOP_SHOWBASEREQUEST_H
#define LAB2_OOP_SHOWBASEREQUEST_H

#include "Request.h"

class ShowBaseRequest : public Request {
 private:
  Point basePosition;

 public:
  explicit ShowBaseRequest(Point p) : basePosition(p) {}

  void execute(GameInfo &gameInfo) override {
    auto object = gameInfo.getField().getCell(basePosition)->getObject();
    if (object && object->getType() == ObjectType::BASE) {
      auto base = dynamic_cast<Base *>(object);

      game::log << "[Game] Obtained base showcase request" << game::logend;
      std::cout << "[Game] Base info: " << std::endl
                << "\tHP: " << base->getBaseHealth() << std::endl
                << "\tArmor: " << base->getBaseArmor() << std::endl
                << "\tMax Objects Count: " << base->getBaseMaxObjectsCount() << std::endl;

    } else {
      game::log << "[Game] Empty Cell" << game::logend;
    }
  }
};

class ShowBaseRequestHandler : public RequestHandler {
 public:
  bool canHandle(std::vector<std::string> &cmd) override {
    return cmd.size() == 3 && cmd[0] == "base";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override {
    if (canHandle(cmd)) {
      int x = std::stoi(cmd[1]);
      int y = std::stoi(cmd[2]);
      Point basePosition(x, y);
      return RequestPtr(new ShowBaseRequest(basePosition));
    }

    if (next) return next->handle(cmd);
    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_SHOWBASEREQUEST_H

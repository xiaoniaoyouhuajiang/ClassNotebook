#ifndef LAB2_OOP_ATTACKUNITREQUEST_H
#define LAB2_OOP_ATTACKUNITREQUEST_H

#include "Request.h"

class AttackUnitRequest : public Request {
 private:
  Point from;
  Point to;

 public:
  AttackUnitRequest(Point from, Point to) : from(from), to(to) {}

  void execute(GameInfo &gameInfo) override {
    auto firstObject = gameInfo.getField().getCell(from)->getObject();
    auto secondObject = gameInfo.getField().getCell(to)->getObject();
    if (firstObject && firstObject->getType() == ObjectType::UNIT && secondObject && secondObject->getType() == ObjectType::UNIT) {
      auto firstUnit = dynamic_cast<Unit *>(firstObject);
      auto secondUnit = dynamic_cast<Unit *>(secondObject);
      game::log << "[Game] Obtained attack request" << game::logend;
      firstUnit->attack(*secondUnit);
    } else
      game::log << "[Game] It's impossible to attack" << game::logend;
  }

  RequestMemento * getMemento() const override {
    std::stringstream stream;
    stream << "attack unit " << from.x << " " << from.y << " " << to.x << " " << to.y << std::endl;
    return new RequestMemento(stream.str());
  }
};

class AttackUnitRequestHandler : public RequestHandler {
 public:
  bool canHandle(std::vector<std::string> &cmd) override {
    return cmd.size() == 5 && cmd[0] == "unit";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override {
    if (canHandle(cmd)) {
      int x1 = std::stoi(cmd[1]);
      int y1 = std::stoi(cmd[2]);
      int x2 = std::stoi(cmd[3]);
      int y2 = std::stoi(cmd[4]);
      Point from(x1, y1);
      Point to(x2, y2);
      return RequestPtr(new AttackUnitRequest(from, to));
    }

    if (next)
      return next->handle(cmd);
    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_ATTACKUNITREQUEST_H

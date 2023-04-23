#ifndef LAB2_OOP_MOVEUNITREQUEST_H
#define LAB2_OOP_MOVEUNITREQUEST_H

#include "Request.h"

class MoveUnitRequest : public Request {
 private:
  Point from;
  Point to;

 public:
  MoveUnitRequest(Point from, Point to) : from(from), to(to) {}
  void execute(GameInfo &gameInfo) override {
    auto object = gameInfo.getField().getCell(from)->getObject();
    if (object && object->getType() == ObjectType::UNIT) {
      auto unit = dynamic_cast<Unit *>(object);
      game::log << "[Game] Obtained unit movement request" << game::logend;
      unit->move(to);
    } else
      game::log << "[Game] No unit is placed on this cell" << game::logend;
  }

  RequestMemento * getMemento() const override {
    std::stringstream stream;
    stream << "move unit " << from.x << " " << from.y << " " << to.x << " " << to.y << std::endl;
    return new RequestMemento(stream.str());
  }
};

class MoveUnitRequestHandler : public RequestHandler {
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
      return RequestPtr(new MoveUnitRequest(from, to));
    }

    if (next)
      return next->handle(cmd);
    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_MOVEUNITREQUEST_H

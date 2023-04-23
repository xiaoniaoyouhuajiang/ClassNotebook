#ifndef LAB2_OOP_CREATEUNITREQUEST_H
#define LAB2_OOP_CREATEUNITREQUEST_H

#include "Request.h"
#include "../../Unit/Unit.h"
#include "../../Unit/Viking/SwordMan.h"
#include "../../Unit/Viking/Berserk.h"
#include "../../Unit/Archer/Sniper.h"
#include "../../Unit/Archer/CrossBowMan.h"
#include "../../Unit/Wizard/IceMage.h"
#include "../../Unit/Wizard/FireMage.h"

class CreateUnitRequest: public Request {
 private:
  Point unitPosition;
  UnitType unitType;

 public:
  explicit CreateUnitRequest(Point position, UnitType unitType): unitPosition(position), unitType(unitType){}
  void execute(GameInfo &gameInfo) override {
    if (!gameInfo.getCurrentPlayerBase()){
      game::log << "[Game] Can't create unit without a base" << game::logend;
      return;
    }

    game::log << "[Game] Obtained unit creation request" << game::logend;

    switch (unitType) {
      case UnitType::VIKING:
        gameInfo.getCurrentPlayerBase()->createUnit<Berserk>(unitPosition);
        break;
      case UnitType::ARCHER:
        gameInfo.getCurrentPlayerBase()->createUnit<CrossBowMan>(unitPosition);
        break;
      case UnitType::WIZARD:
        gameInfo.getCurrentPlayerBase()->createUnit<IceMage>(unitPosition);
        break;
      case UnitType::UNKNOWN:break;
    }
  }

  RequestMemento * getMemento() const override{
    std::stringstream stream;
    stream << "create unit " << unitPosition.x << " " << unitPosition.y << " " << Unit::getRawUnitType(unitType) << std::endl;
    return new RequestMemento(stream.str());
  }
};

class CreateUnitRequestHandler: public RequestHandler {
 public:
  bool canHandle(std::vector<std::string> &cmd) override{
    return cmd.size() == 4 && cmd[0] == "unit";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override {
    if (canHandle(cmd)){
      int x = std::stoi(cmd[1]);
      int y = std::stoi(cmd[2]);
      auto uppercasedType = cmd[3];
      int i = 0;
      while (uppercasedType[i]) {
        uppercasedType[i] = toupper(uppercasedType[i]);
        i++;
      }
      UnitType requestedUnitType = Unit::getUnitTypeFromString(uppercasedType);
      if (requestedUnitType == UnitType::UNKNOWN) {
        if (next)
          return next->handle(cmd);
        else
          return std::make_unique<Request>();
      }
      Point basePosition(x, y);
      return RequestPtr(new CreateUnitRequest(basePosition, requestedUnitType));
    }

    if (next)
      return next->handle(cmd);
    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_CREATEUNITREQUEST_H

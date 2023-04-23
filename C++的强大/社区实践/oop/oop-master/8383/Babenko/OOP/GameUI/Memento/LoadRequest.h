#ifndef LAB2_OOP_LOADREQUEST_H
#define LAB2_OOP_LOADREQUEST_H

#include "../LoadedRequestInterpreter.h"
#include "../../Utils.h"
#include "../../Exceptions/InvalidFileLoaddingException.h"
#include "../../Exceptions/DoublePlacingOnFieldException.h"
#include "../../Exceptions/GameFieldOutOfRangeException.h"
#include "../../Exceptions/ImpossibleMoveException.h"

class LoadRequest : public Request {
 private:
  std::ifstream fileStream;
  LoadedRequestInterpreter interpreter;

 public:
  explicit LoadRequest(std::string &fileName) : fileStream(fileName) {}
  void execute(GameInfo &gameInfo) override {
    gameInfo.createNewGame();
    std::string requestLine;

    std::hash<std::string> hashFunction;
    unsigned long long calculatedHash = 0;
    unsigned long long fileHash = 0;

    std::string fileHashString;
    std::getline(fileStream, fileHashString);

    fileHash = Utils::StrToInt(fileHashString);

    while (std::getline(fileStream, requestLine)) {
      RequestPtr request = interpreter.handle(requestLine);
      try {
        request->execute(gameInfo);
      } catch (DoubleBasePlacingException &exception) {
        game::log << "[FileLoader]" << "Player " << exception.playerIndex << " trying to place base second time."
                  << game::logend;
      } catch (DoublePlacingOnFieldException &exception) {
        game::log << "[FileLoader]" << "This cell is busy by the other object." << game::logend;
      } catch (GameFieldOutOfRangeException &exception) {
        game::log << "[FileLoader]" << "Out of range. Cell " << exception.x << " " << exception.y << " does not exist."
                  << game::logend;
      } catch (ImpossibleMoveException &exception) {
        game::log << "[FileLoader]" << "Can't move to this cell. It's busy by the other object." << game::logend;
      } catch (...) {
        game::log << "[FileLoader]" << "Undefined error." << game::logend;
      }
      auto memento = request->getMemento();
      gameInfo.addToHistoricalData(memento);
      calculatedHash += memento->getHash(hashFunction);
      gameInfo.nextUser();
    }

    game::log << "[Memento] String hash from file: " << fileHashString << game::logend;
    game::log << "[Memento] Int hash from file: " << fileHash << game::logend;
    game::log << "[Memento] Calculated hash: " << calculatedHash << game::logend;
    game::log << "[Memento] Read requests count: " << gameInfo.getHistoricalData().size() << game::logend;

    if (fileHash != calculatedHash) {
      game::log << "[Memento] Wrong file format. The correctness of the loaded field is not guaranteed."
                << game::logend;
      throw InvalidFileLoaddingException();
    }
  }

  ~LoadRequest() override {
    fileStream.close();
  }
};

class LoadRequestHandler : public RequestHandler {
 public:
  bool canHandle(std::vector<std::string> &cmd) override {
    return cmd.size() == 2 && cmd[0] == "load";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override {
    if (canHandle(cmd)) {
      return RequestPtr(new LoadRequest(cmd[1]));
    }

    if (next)
      return next->handle(cmd);
    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_LOADREQUEST_H

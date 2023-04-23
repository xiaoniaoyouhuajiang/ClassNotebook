#ifndef LAB2_OOP_SAVEREQUEST_H
#define LAB2_OOP_SAVEREQUEST_H

#include "../Requests/Request.h"

class SaveRequest : public Request {
 private:
  std::ofstream fileStream;

 public:
  explicit SaveRequest(std::string &filename) : fileStream(filename) {
    game::log << "[Memento] File to save is opened" << game::logend;
    game::log << "[Memento] File to save is opened = " << fileStream.is_open() << game::logend;
  }
  void execute(GameInfo &gameInfo) override {
    std::hash<std::string> hashFunction;
    unsigned long long fileHash = 0;

    game::log << "[Memento] Saving..." << game::logend;
    auto historicalData = gameInfo.getHistoricalData();

    for (auto data: historicalData) {
      fileHash += data->getHash(hashFunction);
    }

    fileStream << fileHash << std::endl;

    for (auto data: historicalData) {
      data->saveToFile(fileStream);
    }

    game::log << "[Memento] Saved requests count: " << gameInfo.getHistoricalData().size() << game::logend;
  }

  ~SaveRequest() override {
    game::log << "[Memento] File to save is closed" << game::logend;
    fileStream.close();
    game::log << "[Memento] File to save is open = " << fileStream.is_open() << game::logend;
  }
};

class SaveRequestHandler : public RequestHandler {
  bool canHandle(std::vector<std::string> &cmd) override {
    return cmd.size() == 2 && cmd[0] == "save";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override {
    if (canHandle(cmd)) {
      return RequestPtr(new SaveRequest(cmd[1]));
    }

    if (next)
      return next->handle(cmd);

    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_SAVEREQUEST_H

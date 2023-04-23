#include "facade.h"

Facade::Facade(Ui::MainWindow *ui, Game *game): ui(ui), game(game)
{
    logger = new Adapter(new ProxyLogger(TOTERMINAL));
}

void Facade::getGameInfo()
{
   GameCommand com(game, GAME_INFO, map<string, Data>());
   map<string, int> answers = com.mainInfoAboutObj();
   string output{};
   for(auto it = answers.begin(); it != answers.end(); ++it) {
         output+=it->first + to_string(it->second)+"\n";
   }
   ui->logWindow->append(QString::fromStdString(output));
   logger->makeLog(GAME_INFO, answers);
}

void Facade::getBaseInfo(int number)
{
    map<string, Data> params;
    Data data;
    data.x = number;
    params["base num"] = data;
    GameCommand com(game, BASE_INFO, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first + to_string(it->second)+"\n";
    }
    ui->infoWindow->append(QString::fromStdString(output));
    logger->makeLog(BASE_INFO, answers);
}

void Facade::getUnitInfo(int x, int y)
{
    map<string, Data> params;
    Data data;
    data.x = x;
    data.y = y;
    params["infoParams"] = data;
    GameCommand com(game, UNIT_INFO, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first + to_string(it->second)+"\n";
    }
    ui->infoWindow->append(QString::fromStdString(output));
    logger->makeLog(UNIT_INFO, answers);
}

void Facade::getNeutralInfo(int x, int y)
{
    map<string, Data> params;
    Data data;
    data.x = x;
    data.y = y;
    params["infoParams"] = data;
    GameCommand com(game, NEUTRAL_INFO, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
        output+=it->first;
        if(it->second != 0)
            output+= convertFromEnumToNeutral(static_cast<NeutralType>(it->second))+"\n";
    }
    ui->infoWindow->append(QString::fromStdString(output));
    logger->makeLog(NEUTRAL_INFO, answers);
}

void Facade::getLandscapeInfo(int x, int y)
{
    map<string, Data> params;
    Data data;
    data.x = x;
    data.y = y;
    params["infoParams"] = data;
    GameCommand com(game, LAND_CELL, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
        output+=it->first;
        if(it->second != 0)
            output+= convertFromEnumToLand(static_cast<LandscapeType>(it->second))+"\n";
    }
    ui->infoWindow->append(QString::fromStdString(output));
    logger->makeLog(LAND_CELL, answers);
}

void Facade::moveUnit(int x, int y, int xDelta, int yDelta)
{
    map<string, Data> params;
    Data data;
    data.x = x;
    data.y = y;
    params["pos"] = data;
    Data dataMove;
    dataMove.x = xDelta;
    dataMove.y = yDelta;
    params["move"] = dataMove;
    GameCommand com(game, MOVE, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first + to_string(it->second)+"\n";
    }
    ui->logWindow->append(QString::fromStdString(output));
    logger->makeLog(MOVE, answers);
}

void Facade::attackUnit(int x, int y, int xDelta, int yDelta)
{
    map<string, Data> params;
    Data data;
    data.x = x;
    data.y = y;
    params["pos"] = data;
    Data dataAttack;
    dataAttack.x = xDelta;
    dataAttack.y = yDelta;
    params["attack pos"] = dataAttack;
    GameCommand com(game, ATTACK, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first + to_string(it->second)+"\n";
    }
    ui->logWindow->append(QString::fromStdString(output));
    logger->makeLog(ATTACK, answers);
}

void Facade::addBase(int x, int y, int maxUnitsCount, int health)
{
    int baseNum = game->getBases().size();
    map<string, Data> params;
    Data dataPos;
    dataPos.x = x;
    dataPos.y = y;
    params["pos"] = dataPos;
    Data addParams{};
    addParams.x = maxUnitsCount;
    addParams.y = health;
    addParams.base = baseNum;
    params["addParams"] = addParams;
    GameCommand com(game, BASE_ADD, params);
    map<string, int> answers;
    try{
        answers = com.mainInfoAboutObj();
    }catch(invalid_argument& e){
        answers[e.what()]=0;
    }
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first +"\n";
    }
    ui->logWindow->append(QString::fromStdString(output));
    logger->makeLog(BASE_ADD, answers);
}

void Facade::addUnit(int base, int type)
{
    map<string, Data> params;
    Data data;
    data.base = base;
    data.unitType = static_cast<UnitsType>(type);
    params["addParams"] = data;
    GameCommand com(game, UNIT_ADD, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first+"\n";
    }
    ui->logWindow->append(QString::fromStdString(output));
    logger->makeLog(UNIT_ADD, answers);
}

void Facade::addNeutral(int x, int y, int type)
{
      map<string, Data> params;
      Data data;
      data.x = x;
      data.y = y;
      data.neutralType = static_cast<NeutralType>(type);
      params["addParams"] = data;
      GameCommand com(game, NEUTRAL_ADD, params);
      map<string, int> answers = com.mainInfoAboutObj();
      string output{};
      for(auto it = answers.begin(); it != answers.end(); ++it) {
            output+=it->first+"\n";
      }
      ui->logWindow->append(QString::fromStdString(output));
      logger->makeLog(NEUTRAL_ADD, answers);
}

Adapter *Facade::getLogger() const
{
    return logger;
}

void Facade::setLogger(LogPlace logPlace)
{
    logger->setLogger(new ProxyLogger(logPlace));
}

Facade::~Facade()
{
    delete logger;
}


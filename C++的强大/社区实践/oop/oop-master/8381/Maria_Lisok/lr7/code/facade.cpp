#include "exception.h"
#include "facade.h"

Facade::Facade(Ui::MainWindow *ui, Game *game): ui(ui), game(game)
{
    logger = new Adapter(new ProxyLogger(NOLOG));
}

string Facade::getGameInfo()
{
   GameCommand com(game, GAME_INFO, map<string, Data>());
   map<string, int> answers = com.mainInfoAboutObj();
   string output{};
   for(auto it = answers.begin(); it != answers.end(); ++it) {
         output+=it->first + to_string(it->second)+"\n";
   }
   ui->logWindow->append(QString::fromStdString(output));
   logger->makeLog(GAME_INFO, answers);
   return output;
}

string Facade::getBaseInfo(int number)
{
    map<string, Data> params;
    Data data;
    data.x = number;
    params["base num"] = data;
    GameCommand com(game, BASE_INFO, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first;
          if(it->second>=0)
              output+= to_string(it->second)+"\n";
          else
              output+="\n";
    }
    ui->infoWindow->append(QString::fromStdString(output));
    logger->makeLog(BASE_INFO, answers);
    return output;
}

string Facade::getUnitInfo(int x, int y)
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
        output+=it->first + " ";
        if(it->second>=0)
            output+= to_string(it->second)+"\n";
        else
            output+="\n";
    }
    ui->infoWindow->append(QString::fromStdString(output));
    logger->makeLog(UNIT_INFO, answers);
    return output;
}

string Facade::getNeutralInfo(int x, int y)
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
        output+=it->first + " ";
        if(it->first == "neutal type:")
            output+= convertFromEnumToNeutral(static_cast<NeutralType>(it->second))+"\n";
        else if(it->second>=0){
            output+= to_string(it->second)+"\n";
        }
        else
            output+= "\n";
    }
    ui->infoWindow->append(QString::fromStdString(output));
    logger->makeLog(NEUTRAL_INFO, answers);
    return output;
}

string Facade::getLandscapeInfo(int x, int y)
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
        output+=it->first + " ";
        if(it->first == "landscape type:")
            output+= convertFromEnumToLand(static_cast<LandscapeType>(it->second))+"\n";
        else if(it->second>=0){
            output+= to_string(it->second)+"\n";
        }
        else
            output+= "\n";
    }
    ui->infoWindow->append(QString::fromStdString(output));
    logger->makeLog(LAND_CELL, answers);
    return output;
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
         output+=it->first + " ";
         if(it->first ==  "\nmove unit name: "){
             output+= convertFromEnumToUnit(static_cast<UnitsType>(it->second))+"\n";
         }
         else if(it->second>=0){
             output+= to_string(it->second)+"\n";
         }else
             output+= "\n";
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
          output+=it->first;
          if(it->second>=0){
              output+= to_string(it->second)+"\n";
          }else
              output+= "\n";

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
    }catch (CoordsException& e) {
        answers[e.what()]=-1;
        return;
    }catch (CellBusyExpeption& e) {
        answers[e.what()]=-1;
        return;
    }catch (SimpleFieldException& e) {
        answers[e.what()]=-1;
        return;
    }catch (LandExeption& e) {
        answers[e.what()]=-1;
        return;
    }
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
        output+=it->first + " ";
        if(it->second>=0)
            output+= to_string(it->second)+"\n";
        else
            output+= "\n";
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
        output+=it->first + " ";
        if(it->second>=0)
            output+= to_string(it->second)+"\n";
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
          output+=it->first + " ";
          if(it->first == "neutral type: ")
              output+= convertFromEnumToNeutral(static_cast<NeutralType>(it->second))+"\n";
          else if(it->second>=0){
              output+= to_string(it->second)+"\n";
          }
          else
              output+= "\n";

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
    try {
        logger->setLogger(new ProxyLogger(logPlace));
    } catch (SimpleFieldException& e) {
        ui->logWindow->append(QString::fromStdString(e.what()));
    }
}

void Facade::saveGame(string name)
{
    try {
        game->readMemento(name);
    } catch (LandExeption& a) {
        string output;
        output += "Error while loading game: ";
        output += a.what();
        ui->logWindow->append(QString::fromStdString(output));
    }catch (SimpleFieldException& a) {
        string output;
        output += "Error while loading game: ";
        output += a.what();
        ui->logWindow->append(QString::fromStdString(output));
    }catch (CellBusyExpeption& a) {
        string output;
        output += "Error while loading game: ";
        output += a.what();
        ui->logWindow->append(QString::fromStdString(output));
    }catch (CoordsException& a) {
        string output;
        output += "Error while loading game: ";
        output += a.what();
        ui->logWindow->append(QString::fromStdString(output));
    }
}

void Facade::loadGame(string name)
{
    try {
        GameMemento *memento = new GameMemento(name);
        game->restoreMemento(memento);
        GameCommand com(game, GAME_INFO, map<string, Data>());
        map<string, int> answers = com.mainInfoAboutObj();
        string output{};
        for(auto it = answers.begin(); it != answers.end(); ++it) {
              output+=it->first + to_string(it->second)+"\n";
        }
        ui->logWindow->append(QString::fromStdString(output));
    }catch (CoordsException& a) {
        std::string output;
        output += "Runtime error while loading game: ";
        output += a.what();
        ui->logWindow->append(QString::fromStdString(output));
    }catch (CellBusyExpeption& a) {
        std::string output;
        output += "Logic error while loading game: ";
        output += a.what();
        ui->logWindow->append(QString::fromStdString(output));
    }catch (SimpleFieldException& a) {
        std::string output;
        output += "Logic error while loading game: ";
        output += a.what();
        ui->logWindow->append(QString::fromStdString(output));
    }catch (LandExeption& a) {
        std::string output;
        output += "Logic error while loading game: ";
        output += a.what();
        ui->logWindow->append(QString::fromStdString(output));
    }
}

Facade::~Facade()
{
    delete logger;
}


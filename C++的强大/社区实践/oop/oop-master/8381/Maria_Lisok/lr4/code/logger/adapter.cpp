#include "adapter.h"

Adapter::Adapter(Logger * logger): logger(logger)
{
}

Adapter::~Adapter()
{
    delete logger;
    logger = nullptr;
}

void Adapter::setLogger(Logger *value)
{
    logger = value;
}

void Adapter::makeLog(Actions act, map<string, int> data)
{
    if(logger->isActive()){
        if(act == BASE_INFO){
            logger->prinLog(baseInfoLog(data));
        }else if(act == GAME_INFO){
            logger->prinLog(gameInfoLog(data));
        }else if(act == LAND_CELL){
            logger->prinLog(landCellInfo(data));
        }else if(act == NEUTRAL_INFO){
            logger->prinLog(neutralInfoLog(data));
        }else if(act == UNIT_INFO){
            logger->prinLog(userInfoLog(data));
        }else if(act == MOVE){
            logger->prinLog(moveLog(data));
        }else if(act == ATTACK){
            logger->prinLog(attackLog(data));
        }else if(act == BASE_ADD){
            logger->prinLog(baseAddLog(data));
        }else if(act == UNIT_ADD){
            logger->prinLog(unitAddLog(data));
        }else if(act == NEUTRAL_ADD){
            logger->prinLog(neutralAddLog(data));
        }
    }
}

string Adapter::baseAddLog(map<string, int> data)
{
    string info{};
    info += "Information about action add base:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        info +=it->first + to_string(it->second)+"\n";
    }
    return info;
}

string Adapter::neutralAddLog(map<string, int> data)
{
    string info{};
    info += "Information about action add neutral:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->second <0){
            info +=it->first;
        }else if(it->first.compare("neutal type: ")==0){
            info +=it->first;
            info += convertFromEnumToNeutral(static_cast<NeutralType>(it->second))+"\n";
        }else{
            info +=it->first + to_string(it->second)+"\n";
        }
    }
    return info;
}

string Adapter::unitAddLog(map<string, int> data)
{
    string info{};
    info += "Information about action add unit:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->second <0){
            info +=it->first;
        } else{
            info +=it->first + to_string(it->second)+"\n";
        }
    }
    return info;
}

string Adapter::attackLog(map<string, int> data)
{
    string info{};
    info += "Attack info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->second < 0)
            info +=it->first + "\n";
        else{
            info +=it->first + to_string(it->second)+"\n";
        }
    }
    return info;
}

string Adapter::moveLog(map<string, int> data)
{
    string info{};
    info += "Move info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->first.compare("move unit name: ")==0){
            info +=it->first;
            info += convertFromEnumToUnit(static_cast<UnitsType>(it->second));
        } else{
            info +=it->first + to_string(it->second)+"\n";
        }
    }
    return info;
}

string Adapter::gameInfoLog(map<string, int> data)
{
    string info{};
    info += "Game info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
          info +=it->first + to_string(it->second)+"\n";
    }
    return info;
}

string Adapter::baseInfoLog(map<string, int> data)
{
    string info{};
    info += "Base info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        info +=it->first + to_string(it->second)+"\n";
    }
    return info;
}

string Adapter::userInfoLog(map<string, int> data)
{
    string info{};
    info += "User info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->second <0){
            info +=it->first;
        } else{
            info +=it->first + to_string(it->second)+"\n";
        }
    }
    return info;
}

string Adapter::neutralInfoLog(map<string, int> data)
{
    string info{};
    info += "Neutral info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->second <0){
            info +=it->first;
        }else if(it->first.compare("neutal type:")==0){
            info +=it->first;
            info += convertFromEnumToNeutral(static_cast<NeutralType>(it->second))+"\n";
        }else{
            info +=it->first + to_string(it->second)+"\n";
        }
    }
    return info;
}

string Adapter::landCellInfo(map<string, int> data)
{
    string info{};
    info += "Land cell info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->second <0){
            info +=it->first;
        }else if(it->first.compare("landscape type:")==0){
            info +=it->first;
            info += convertFromEnumToLand(static_cast<LandscapeType>(it->second))+"\n";
        }else{
            info +=it->first + to_string(it->second)+"\n";
        }
    }
    return info;
}



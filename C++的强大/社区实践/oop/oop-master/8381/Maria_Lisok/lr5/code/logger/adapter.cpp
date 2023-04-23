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
    if(logger){
        delete logger;
    }
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
    info += "\nInformation about action add base:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        info+=it->first + " ";
        if(it->second>=0)
            info+= to_string(it->second)+"\n";
        else
            info+= "\n";

    }
    return info;
}

string Adapter::neutralAddLog(map<string, int> data)
{
    string info{};
    info += "\nInformation about action add neutral:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->second <0){
            info +=it->first + "\n";
        }else if(it->first == "neutral type: "){
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
    info += "\nInformation about action add unit:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->second <0){
            info +=it->first + "\n";
        } else{
            info +=it->first + to_string(it->second)+"\n";
        }
    }
    return info;
}

string Adapter::attackLog(map<string, int> data)
{
    string info{};
    info += "\nAttack info:\n";
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
    info += "\nMove info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->first == "\nmove unit name: "){
            info +=it->first;
            info += convertFromEnumToUnit(static_cast<UnitsType>(it->second))+"\n";
        }else if(it->second < 0){
            info +=it->first + "\n";
        }else{
            info +=it->first + to_string(it->second)+"\n";
        }
    }
    return info;
}

string Adapter::gameInfoLog(map<string, int> data)
{
    string info{};
    info += "\nGame info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
          info +=it->first + to_string(it->second)+"\n";
    }
    return info;
}

string Adapter::baseInfoLog(map<string, int> data)
{
    string info{};
    info += "\nBase info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        info+=it->first + " ";
        if(it->second>=0)
            info+= to_string(it->second)+"\n";
        else
            info+= "\n";
    }
    return info;
}

string Adapter::userInfoLog(map<string, int> data)
{
    string info{};
    info += "\nUser info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->second <0){
            info +=it->first + "\n";
        } else{
            info +=it->first + to_string(it->second)+"\n";
        }
    }
    return info;
}

string Adapter::neutralInfoLog(map<string, int> data)
{
    string info{};
    info += "\nNeutral info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->second <0){
            info +=it->first + "\n";
        }else if(it->first == "neutal type:"){
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
    info += "\nLand cell info:\n";
    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it->second <0){
            info +=it->first;
        }else if(it->first == "landscape type:"){
            info +=it->first;
            info += convertFromEnumToLand(static_cast<LandscapeType>(it->second))+"\n";
        }else{
            info +=it->first + to_string(it->second)+"\n";
        }
    }
    return info;
}



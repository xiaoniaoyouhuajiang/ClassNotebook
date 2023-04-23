#include "Logger.h"
#include <sstream>
#include "Units.h"
#include "Base.h"
#include "Game.h"
#include <string>



Logger::Logger(){
    outputFile.exceptions(std::ofstream::badbit| std::ofstream::failbit);
    try{
        outputFile.open(::logsName, std::ofstream::out|std::ofstream::app);
    }
    catch(const std::ofstream::failure& ex){
        ex.what();
        ex.code();
    }
}

Logger::~Logger(){
    outputFile.close();
}

void Logger::request(LogInfo* log){
    outputFile<<(*log); 
}

void LogProxy::request(LogInfo* log){
    switch (type) {
        case CONSOLE:
            std::cout<<(*log);
            break;
        case INFILE:
            logger->request(log);
            break;
        case CONSOLE_AND_FILE:
            std::cout<<(*log);
            logger->request(log);
            break;
        default:
            break;
    }
}

TypeLog LogProxy::getType(){
    return type;
}



//-----------------------ADAPTER-------------------------------//
void Adapter::InfoUnit(Unit* unit){
    std::stringstream messageForLog;
    messageForLog<<"Unit info: hp - "<<unit->hitPoint<<" mp - "<<unit->manaPoint<<" magic resist - "<< unit->magicResistance<<" armor - "<<unit->armor;
    request(new LogInfo(messageForLog.str()));
}

void Adapter::InfoBase(Base *base){
    std::stringstream messageForLog;
    messageForLog<<"Base info: hp - "<<base->hitPoint<<" max unit - "<< base->maxUnit<<" count of units defined to this base"<<base->unitsInBase;
    request(new LogInfo(messageForLog.str()));
}

void  Adapter::InfoAttack(Unit *unit, Unit *enemy, int damage){
    std::stringstream messageForLog;
    if(unit->isNPC == true){
        messageForLog<<"NPC ";
    }
    else{
         messageForLog<<"Unit ";
    }
    messageForLog<<" standing on("<<unit->x<<","<<unit->y<<") attack ";
    if(enemy->isNPC == true){
        messageForLog<<"NPC ";
    }
    else{
         messageForLog<<"unit ";
    }
    messageForLog<<" standing on("<<enemy->x<<","<<enemy->y<<"). Damage: "<<damage<<" info about enemy: ";
    request(new LogInfo(messageForLog.str()));
    InfoUnit(enemy);
    
}

void Adapter::InfoAttack(Unit *unit, Base *base, int damage){
    std::stringstream messageForLog;
    messageForLog<<" Unit standing on("<<unit->x<<","<<unit->y<<") attack base on ("<<base->x<<","<<base->y<<"). Damage: "<<damage;
    request(new LogInfo(messageForLog.str()));
}

void Adapter::InfoMove(Unit *unit, int oldCoordX, int oldCoordY){
    std::stringstream messageForLog;
    if(unit->isNPC == true){
        messageForLog<<"NPC ";
    }
    else{
         messageForLog<<"Unit ";
    }
    messageForLog<<"standing on("<<oldCoordX<<","<<oldCoordY<<") move; New coord ("<<unit->x<<","<<unit->y<<")";
    request(new LogInfo(messageForLog.str()));
}

void Adapter::InfoStr(std::string mess){
    std::stringstream messageForLog;
    messageForLog<<mess;
    request(new LogInfo(messageForLog.str()));
}

void Adapter::InfoErrorCode(const std::error_code &code){
    std::stringstream messageForLog;
    messageForLog<<"Error code: "<<code.value()<<" "<<code.message();
    request(new LogInfo(messageForLog.str()));
}


#include "Command.h"
#include "Units.h"
#include "GameEntity.h"
#include "Map.h"
#include "GameBlock.h"
#include "Base.h"
#include "GameMaster.h"
#include "Exeptions.h"

void HelpCommand::execute(){
    std::cout<<"wasd - for move, h - help, f - attack, u - choosing fighter, b - base control, p - stop, o - options, e - exit" <<std::endl;
}

void MoveCommand::execute(){
    if((*remainingEnergy) - cost > -1 ){
        if(unitCont->moveUnit(x, y, index, *map, death)){
            (*remainingEnergy) = (*remainingEnergy)- cost;
        }
    }
}

void AttackCommand::execute(){
    if((*remainingEnergy) - cost > -1 ){
        if(unitCont->attack(index, *map, enemiesV) == true){
            (*remainingEnergy) = (*remainingEnergy)- cost;
        }
    }
}




void CreateUnitInBaseCommand::execute(){
     if((*remainingEnergy) - cost > -1 ){
         if(baseCont->createUnit() == 0){
             (*remainingEnergy) = (*remainingEnergy)- cost;
         }
     }
}


void BaseStatCommand::execute(){
    baseCont->showStat();
}


void SelectUnitInBaseCommand::execute(){
    while(1){
        newUnit = baseCont->getUnit();
        if(newUnit == nullptr){
            unitCont->currentUnit = -1;
            break;
        }
        else{
            unitCont->addUnit(newUnit, baseCont->x, baseCont->y, *map);
            unitCont->currentUnit = unitCont->units.size() - 1;
            break;
        }
    }
}



void SwitchUnitCommand::execute(){
    (*index) = unitCont->changeActiveUnit();
}



SaveLoadCommand::~SaveLoadCommand(){
    delete memento;
}

BaseCommand::~BaseCommand(){
    delete baseCont;
}

UnitCommand::~UnitCommand(){
    delete unitCont;
    delete remainingEnergy;
}

SwitchUnitCommand::~SwitchUnitCommand(){
    delete unitCont;
    delete index;
}

MoveCommand::~MoveCommand(){
    delete map;
    delete death;
}

AttackCommand::~AttackCommand(){
    delete map;
}

SelectUnitInBaseCommand::~SelectUnitInBaseCommand(){
    delete unitCont;
    delete newUnit;
    delete map;
}

//CreateBaseCommand::~CreateBaseCommand(){
//    delete map;
//}


//---------------------SaveLoadCommand----------------------//
SaveFCommand::SaveFCommand(GameMaster::Memento* memento):SaveLoadCommand(memento){
    saveFile.exceptions(std::ofstream::badbit| std::ofstream::failbit);
    Adapter* a = new Adapter;
    a->InfoStr("Open file for save:");
    a->InfoStr(fileName);
    try{
        saveFile.open(fileName, std::ofstream::out);
        a->InfoStr("Success");
        delete a;
    }
    catch(const std::ofstream::failure& ex){
        ex.what();
        ex.code();
        
        a->InfoStr (ex.what());
        a->InfoErrorCode(ex.code());
        delete a;
    }
}

SaveFCommand::~SaveFCommand(){
    saveFile.close();
}

void SaveFCommand::execute(){
    saveFile<<*memento;
}


LoadFCommand::LoadFCommand(GameMaster::Memento* memento, GameMaster* gm):SaveLoadCommand(memento), gm(gm){
    saveFile.exceptions(std::ifstream::badbit| std::ifstream::failbit);
    Adapter* a = new Adapter;
    a->InfoStr("Open file for load:");
    a->InfoStr(fileName);
    try{
        saveFile.open(fileName, std::ofstream::in);
        a->InfoStr("Success");
        delete a;
    }
    catch(const std::ifstream::failure& ex){
        a->InfoStr (ex.what());
        a->InfoErrorCode(ex.code());
        delete a;
        throw ex;
    }
}

LoadFCommand::~LoadFCommand(){
    saveFile.close();
}

void LoadFCommand::execute(){
    try {
        saveFile>>*memento;
    } catch (GameException& ex) {
        Adapter* a = new Adapter;
        a->InfoStr(ex.message());
        std::cout<<"Load error, incorrect data"<<std::endl;
        exit(0);
    }
    
    
    gm->teams.clear();
    gm->teams.push_back(gm->aggressiveNPC);
    gm->teams.push_back(gm->units);
    if(gm->countTeam == 3){
        gm->teams.push_back(gm->enemies);
    }
    gm->updateLogs();
}



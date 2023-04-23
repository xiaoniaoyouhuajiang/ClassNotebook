
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "GameMaster.h"
#include "Map.h"
#include "Base.h" 
#include "Units.h"
#include "GameVisualization.h"
#include "GameBlock.h"
#include "NeutralObject.h"
#include "GameEntity.h"
#include "Invoker.h"
#include "Command.h"
#include "Handler.h"
#include "Logger.h"
#include "Exeptions.h"




GameMaster::GameMaster(){
    srand(time(0));
    map = nullptr;
   
    loggerP = new LogProxy(new Logger());
    units = new TeamEntity;
    enemies = new TeamEntity;
    aggressiveNPC = new TeamEntity(NPC);
    teams.push_back(units);
    teams.push_back(enemies);
    teams.push_back(aggressiveNPC);
    countTeam = 3;
    neutralObjs = new GameNeutralObjects;
    
    firstHandler = new AttackHandler;
    firstHandler->setNext(new MoveHandler)->setNext(new BaseControlHandler)->setNext(new ChangeUnitHandler)->setNext(new HelpHandler)->setNext(new OptionsHandler);
    
    setMap();
    gameVisualization = new GameVisualization(map);
    setEnemies();
    
    updateLogs();
}


cycleEnd GameMaster::gameCycle() {
    char input;
    bool deathCheck = false;
    std::stringstream messageForLog;
    Adapter adapter;
    energyForStep = 8;
    Base* currentBase;
   // setBase();
    //updateLogs();
    if(units->bases.size() != 0 ){
        currentBase = units->bases[units->currentBase];
        firstHandler->handle('b', currentBase, &deathCheck, this);
        gameVisualization->update();
    }
    else{
        gameVisualization->update();
        currentBase = nullptr;
        command = firstHandler->handle('u', currentBase, &deathCheck, this);
        command->execute();
    }
    do {
        if(units->currentUnit == -1){
            firstHandler->handle('b', currentBase, &deathCheck, this);
        }
        
        std::cout << "Remaining energy:"<<energyForStep<<"\nEnter command: ";
        
        try{
            std::cin>>input;
            messageForLog <<"User input: "<<input<<std::endl;
            loggerP->request(new LogInfo(messageForLog.str()));
            messageForLog.str("");
            if(input == 'e'){
                return EXIT;
            }
        }
        catch(const std::istream::failure& ex){
            
            messageForLog <<"User input: "<<input<<std::endl;
            loggerP->request(new LogInfo(messageForLog.str()));
            messageForLog.str("");
            
            adapter.InfoStr("Wrong input");
            adapter.InfoErrorCode(ex.code());
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            input = 'h';
        }
        
        command = firstHandler->handle(input, currentBase, &deathCheck, this);
        
        if(command != nullptr){
                command->execute();
        }
        if(deathCheck){
            
            try{map->getBlock(units->units[units->currentUnit]->y, units->units[ units->currentUnit]->x )->unitOnBlock = nullptr;
            }
            catch(BlockAccessException& ex){
               Adapter a;
               a.InfoStr(ex.message());
               return NEXT;
            }
            units->units.pop_back();
            units->size--;
            if(units->bases.size() != 0){
                units->bases[units->currentBase]->unitsInBase--;
                units->currentUnit--;
                if(energyForStep != 0){
                    firstHandler->handle('b', units->bases[units->currentBase], &deathCheck, this);
                }
            }else if(energyForStep != 0){
                firstHandler->handle('u', units->bases[units->currentBase], &deathCheck, this);
            }
        }
        gameVisualization->update();
        
    } while (!(input == 'p' || energyForStep == 0) );
 
    return NEXT;
}


//------------------------------------------------------------------------------------------------------------------------------------------------

bool GameMaster::checkingVictory(){
    int NPC = 1;
    for(auto it = teams.begin(); it != teams.end(); it++){
        if((*it)->isDefeated == true){
            teams.erase(it);
            it = teams.begin();
            this->countTeam--;
        }
        if(teams.size() - NPC <= 1){
            return true;
        }
    }
    return false;
}

void GameMaster::moveNPC(){
    aggressiveNPC->moveNPC(*map, teams);
}

void GameMaster::spawnUForSurv(){
    int i = 2;
    
    int x, y;
    std::stringstream messageForLog;
    std::cout<<std::endl<<"You can spawn "<<i<<" units. (Only on grass)"<<std::endl;
    while(i){
        gameVisualization->update();

        do{
            std::cout<<"Enter coord for unit (x;y): ";
            std::cin>>x>>y;
            
            messageForLog <<"User input: ("<<x<<";"<<y<<")"<<std::endl;
            loggerP->request(new LogInfo(messageForLog.str()));
            messageForLog.str("");
            
        } while(!(x > 0 && y > 0 && y <= map->getHeight() && x <= map->getWidth() && map->getBlock(y-1, x-1)->isEmpty()));
        x--;
        y--;
    
        Base* tmpBase = new Base(x, y);
        tmpBase->setLog(loggerP);
        tmpBase->createUnit();
        if(tmpBase->units.size() != 0){
             tmpBase->units[0]->setLog(loggerP);
            this->units->addUnit(tmpBase->units[0], x, y, *(map));
        }
        delete tmpBase;
        i--;
    }
}


void GameMaster::spawnNPCForSurv(){
    int x;
    int y;
    do{
        x = rand()% map->getWidth();
        y = rand()% map->getHeight();
    }while(!(x > 0 && y > 0 && y < map->getHeight() && x < map->getWidth() && map->getBlock(y, x)->isEmpty()));
   
    Base* tmpBase = new Base(x, y);
    tmpBase->setLog(loggerP);
    int lytuiRandom = rand()%6;
    switch (lytuiRandom) {
        case 0:
            tmpBase->createUnit('R');
            break;
        case 1:
            tmpBase->createUnit('S');
            break;
        case 2:
            tmpBase->createUnit('W');
            break;
        case 3:
            tmpBase->createUnit('B');
            break;
        case 4:
            tmpBase->createUnit('P');
            break;
        case 5:
            tmpBase->createUnit('L');
            break;
        default:
            tmpBase->createUnit('P');
            break;
    }
    if(tmpBase->units.size() != 0){
        tmpBase->units[0]->setLog(loggerP);
        tmpBase->units[0]->isNPC = true;
        this->aggressiveNPC->addUnit(tmpBase->units[0], x, y, *(map));
        std::cout<<tmpBase->units[0]->type<<" appeared from nowhere"<<std::endl;
    }
    delete tmpBase;
}

//-----------------------------sets----------------//
void GameMaster::setMap(){
    int width, height;
    do{
        width = 9;
        height = 10;
//        std::cout<<"Enter map size: ";
//        std::cin>>width>>height;
        

    } while( !(width > 0 && height > 0));
    map = new GameMap(height, width);

//creating default map
   for(int i = 4; i < 7; i++){
       for(int j = 5; j <8; j++){
           map->getBlock(j, i)->landscape = new Water;
       }
   }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5-i; j++){
            map->getBlock(i, j)->landscape = new Forest;
        }
    }
    int y = 0;
    int x = 5;
    map->getBlock(y,x)->objectOnBlock = new MrWitcher;
    map->getBlock(y,x)->objectOnBlock->setXY(x, y);
    neutralObjs->neutralObjects.push_back(map->getBlock(y,x)->objectOnBlock);
    y = 6;
    x = 2;
    map->getBlock(y,x)->objectOnBlock = new Bonfire;
    map->getBlock(y,x)->objectOnBlock->setXY(x, y);
    neutralObjs->neutralObjects.push_back(map->getBlock(y,x)->objectOnBlock);
    y = 7;
    x = 7;
    map->getBlock(y,x)->objectOnBlock = new Grave;
    map->getBlock(y,x)->objectOnBlock->setXY(x, y);
    neutralObjs->neutralObjects.push_back(map->getBlock(y,x)->objectOnBlock);
    x = 7;
    y = 2;
    map->getBlock(y,x)->objectOnBlock = new Bird;
    map->getBlock(y,x)->objectOnBlock->setXY(x, y);
    neutralObjs->neutralObjects.push_back(map->getBlock(y,x)->objectOnBlock);
    neutralObjs->sizeNO+=4;
}


void GameMaster::setBase(){
    this->gameVisualization->update();
    int x, y;
    std::stringstream messageForLog;
    Adapter adapter;
    do{
        std::cout<<"Enter coord for base (x;y): ";
        try{
            std::cin>>x>>y;
            messageForLog <<"User input: ("<<x<<";"<<y<<")"<<std::endl;
        }
        catch(const std::istream::failure& ex){
            messageForLog <<"User input: ("<<x<<";"<<y<<")"<<std::endl;
            loggerP->request(new LogInfo(messageForLog.str()));
            messageForLog.str("");
            
            adapter.InfoStr("Wrong input");
            adapter.InfoErrorCode(ex.code());
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        
        loggerP->request(new LogInfo(messageForLog.str()));
        messageForLog.str("");
        
    } while(!(x > 0 && y > 0 && y <= map->getHeight() && x <= map->getWidth() && map->getBlock(y-1, x-1)->isEmpty()));
    x--;
    y--;
    
    this->map->getBlock(y, x)->baseOnBlock = new Base(x, y);
    
    units->bases.push_back(this->map->getBlock(y, x)->baseOnBlock);
    units->sizeBase++;
    units->currentBase++;
    
    messageForLog<<"Create base on ("<<x<<";"<<y<<")\n";
    loggerP->request(new LogInfo(messageForLog.str()));
        
    units->bases[units->currentBase]->setLog(loggerP);
    units->bases[units->currentBase]->createUnit('L');
}


void GameMaster::setEnemies(){
    Unit* newEnemy = new Paladin;
    aggressiveNPC->addUnit(newEnemy, 4, 2, *map);
    newEnemy = new LanceKnight;
    aggressiveNPC->addUnit(newEnemy, 0, 6, *map);
    newEnemy = new Slayer;
    aggressiveNPC->addUnit(newEnemy, 2, 7, *map);
    newEnemy = new Witch;
    aggressiveNPC->addUnit(newEnemy, 1, 2, *map);
    for(auto it = aggressiveNPC->units.begin(); it != aggressiveNPC->units.end(); it++){
        (*it)->isNPC = true;
    }
}



void GameMaster::updateLogs(setLog type){
    switch (type) {
        case FORALL:
            for(auto it_ = teams.begin(); it_ != teams.end(); it_++){
                for(auto it = (*it_)->units.begin(); it != (*it_)->units.end(); it++){
                    (*it)->setLog(loggerP);
                }

                for(auto it = (*it_)->bases.begin(); it != (*it_)->bases.end(); it++){
                    (*it)->setLog(loggerP);
                    for( auto it2 = (*it)->units.begin(); it2 != (*it)->units.end(); it2++){
                        (*it2)->setLog(loggerP);
                    }
                }
            }
            for(auto it = neutralObjs->neutralObjects.begin(); it != neutralObjs->neutralObjects.end(); it++){
                (*it)->setLog(loggerP);
            }
            
            for(auto it = aggressiveNPC->units.begin(); it != aggressiveNPC->units.end(); it++){
                (*it)->setLog(loggerP);
            }
            break;
            
        case BASES:
            for(auto it_ = teams.begin(); it_ != teams.end(); it_++)
                   for(auto it = (*it_)->bases.begin(); it != (*it_)->bases.end(); it++){
                       (*it)->setLog(loggerP);
                       for( auto it2 = (*it)->units.begin(); it2 != (*it)->units.end(); it2++){
                           (*it2)->setLog(loggerP);
                       }
            }
                    
        case UNITS:
            for(auto it_ = teams.begin(); it_ != teams.end(); it_++){
                for(auto it = (*it_)->units.begin(); it != (*it_)->units.end(); it++){
                    (*it)->setLog(loggerP);
                }
            }
        case NOBJ:
            for(auto it = neutralObjs->neutralObjects.begin(); it != neutralObjs->neutralObjects.end(); it++){
                (*it)->setLog(loggerP);
            }
        default:
            break;
    }
}
//------------------MEME---------------------//

GameMaster::Memento::Memento( GameMap* map, TeamEntity* units, TeamEntity* enemies,TeamEntity* aggressiveNPC,  GameNeutralObjects* neutralObjs, int* countTeam, int* energyForStep, std::deque<TeamEntity*> teamss):map(map), units(units),enemies(enemies), aggressiveNPC(aggressiveNPC), neutralObjs(neutralObjs), countTeam(countTeam), energyForStep(energyForStep){
    for(auto it = teamss.begin(); it != teamss.end(); it++){
        teams.push_back(*it);
    }
};

std::ostream& operator <<(std::ostream& os, const GameMaster::Memento& meme){
    os<<*(meme.countTeam)<<std::endl;
    os<<*(meme.energyForStep)<<std::endl;
    os<<*(meme.map);
    os<<*(meme.aggressiveNPC);
    os<<*(meme.units);
    if(*(meme.countTeam) == 3){
         os<<*(meme.enemies);
    }
   
    os<<*(meme.neutralObjs);
    return os;
}


std::istream& operator >>(std::istream& os, const GameMaster::Memento& meme){
    try {
        os>>*(meme.countTeam);
    }
    catch (...) {
        throw LoadException(1);
    }
    
    try {
        os>>*(meme.energyForStep);
    }
    catch (...) {
        throw LoadException(2);
    }
    
    try {
         os>>*(meme.map);
    }
    catch (...) {
        throw LoadException(3);
    }
   try {
        os>>*(meme.aggressiveNPC);
   }
    catch (...) {
       throw LoadException(4);
   }
    try {
         os>>*(meme.units);
    }
     catch (...) {
        throw LoadException(5);
    }
    
    
    if(*(meme.countTeam) == 3){
        try {
               os>>*(meme.enemies);
          }
           catch (...) {
              throw LoadException(6);
          }
          
    }
    try {
         os>>*(meme.neutralObjs);
    }
     catch (...) {
        throw LoadException(7);
    }
    
    //set  on map
    int x;
    int y;
    //units
    int size = (int)meme.units->units.size();

    for(int i = 0; i < size; i++){
        x = meme.units->units[i]->x;
        y = meme.units->units[i]->y;
        try{
        meme.map->getBlock(y, x)->unitOnBlock = meme.units->units[i];
        }
        catch(BlockAccessException& ex){
           Adapter a;
           a.InfoStr(ex.message());
            throw LoadException(4, 1);
                          
        }
        
    }
    size = (int)meme.units->bases.size();
    for(int i = 0; i < size; i++){
        x = meme.units->bases[i]->x;
        y = meme.units->bases[i]->y;
        try{
            meme.map->getBlock(y, x)->baseOnBlock = meme.units->bases[i];
        }
        catch(BlockAccessException& ex){
           Adapter a;
           a.InfoStr(ex.message());
            throw LoadException(4,2);
                          
        }

    }
   if(*(meme.countTeam) == 3){
        size = (int)meme.enemies->units.size();
        for(int i = 0; i < size; i++){
            x = meme.enemies->units[i]->x;
            y = meme.enemies->units[i]->y;
            try{
            meme.map->getBlock(y, x)->unitOnBlock = meme.enemies->units[i];
            }
            catch(BlockAccessException& ex){
               Adapter a;
               a.InfoStr(ex.message());
               throw LoadException(4,1);
                              
            }

        }
        size = (int)meme.enemies->bases.size();
        for(int i = 0; i < size; i++){
            x = meme.enemies->bases[i]->x;
            y = meme.enemies->bases[i]->y;
            try{
                meme.map->getBlock(y, x)->baseOnBlock = meme.enemies->bases[i];
            }
            catch(BlockAccessException& ex){
               Adapter a;
               a.InfoStr(ex.message());
               throw LoadException(4,2);
                              
            }
        }
    }
    size = (int)meme.aggressiveNPC->units.size();
    for(int i = 0; i < size; i++){
        x = meme.aggressiveNPC->units[i]->x;
        y = meme.aggressiveNPC->units[i]->y;
        try{
            meme.map->getBlock(y, x)->unitOnBlock = meme.aggressiveNPC->units[i];
        }
        catch(BlockAccessException& ex){
           Adapter a;
           a.InfoStr(ex.message());
           throw LoadException(4,1);
                          
        }
    }
    //neutralObj
    size = meme.neutralObjs->sizeNO;
    for(int i = 0; i < size; i++){
        x = meme.neutralObjs->neutralObjects[i]->x;
        y = meme.neutralObjs->neutralObjects[i]->y;
        try{
            meme.map->getBlock(y, x)->objectOnBlock = meme.neutralObjs->neutralObjects[i];
        }
        catch(BlockAccessException& ex){
           Adapter a;
           a.InfoStr(ex.message());
           throw LoadException(4,3);
                          
        }
    }
  //  update(*(meme.map));
    return os;
};



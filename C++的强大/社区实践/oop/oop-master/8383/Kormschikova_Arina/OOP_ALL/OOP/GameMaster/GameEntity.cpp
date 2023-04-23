#include <cmath>
#include <deque>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <iostream>

#include "GameEntity.h"
#include "Units.h"
#include "Map.h"
#include "GameBlock.h"
#include "Base.h"
#include "NeutralObject.h"
#include "UnitsFactory.h"
#include "Logger.h"
#include "Exeptions.h"


GameUnits::GameUnits(typeU typeu) {
    size = 0;
    type = typeu;
    currentUnit = -1;
}


void GameUnits::addUnit(Unit *unit, int x, int y, GameMap &gameMap){
    this->size++;
    units.push_back(unit);
    units[size-1]->x = x;
    units[size-1]->y = y;
    try {
        gameMap.map[y][x].setUnit(unit);
    } catch (...) {
        Adapter a;
        a.InfoStr(BlockAccessException(x, y).message());
    }
}


Unit* GameUnits::getUnit(int x, int y) {
    for (int i = 0; i < size; i++) {
        if (units[i]->x == x && units[i]->y == y)
            return units[i];
    }
    return nullptr;
}


Base* GameBases:: getBase(int x, int y){
    for(auto it = bases.begin(); it != bases.end(); it++){
        if((*it)->x == x && (*it)->y == y){
            return (*it);
        }
    }
    return nullptr;
}

//
bool GameUnits::moveUnit(int x, int y, int index, GameMap &gameMap, bool* death) {
    bool check = units[index]->move(x, y, gameMap);
    
    if(units[index]->hitPoint < 1){
        *(death) = true;
    }
    else{
        *(death) = false;
    }
    return check;
}


void TeamEntity::update(){
    try{
        for(auto iter = units.begin(); iter != units.end(); iter++){
            if( (*iter)->hitPoint <= 0){
                size--;
                units.erase(iter);
                iter = units.begin();
                if(bases.size() != 0){
                   bases[0]->unitsInBase -=1;
                }
                if(units.empty()){
                    break;
                }
             }
         }
    }
    catch(...){
        
    }
    
    for(auto it = bases.begin(); it != bases.end(); it++){
        if( (*it)->hitPoint <= 0){
            sizeBase--;
            bases.erase(it);
            it = bases.begin();
            if(bases.empty()){
                break;
            }
        }
    }
    
    if(bases.size() == 0 && units.size() == 0 ){
        isDefeated = true;
    }
}


int GameUnits::changeActiveUnit(){
    int index;
    Adapter adapter;
    std::stringstream messageForLog;
    std::cout<<"Choose your fighter"<<std::endl;
    for(int i = 0; i < this->units.size(); i++){
        std::cout<<i+1<<" "<<std::endl;
        this->units[i]->showStat();
    }
    while(1){
        
        try{
            std::cin>>index;
            messageForLog <<"User input: "<<index<<std::endl;
            adapter.InfoStr(messageForLog.str());
       }
       catch(const std::istream::failure& ex){
           std::cout<<"Fail. Default index = 1"<<std::endl;
           messageForLog <<"User input fail: "<<index<<std::endl;
           adapter.InfoStr(messageForLog.str());
           adapter.InfoErrorCode(ex.code());
           std::cin.clear();
           std::cin.ignore(10000, '\n');
           index = 1;
           
       }
        if(index < 1 || index > this->units.size()){
            std::cout<<"Wrong!"<<std::endl;
        }
        else{
            index--;
            return index;
        }
    }
}


bool GameUnits::attack(int index, GameMap &gameMap, std::vector<TeamEntity*> enemies){
    Adapter adapter;
    std::stringstream messageForLog;
    
    int topBorder = (units[index]->y - units[index]->weapon->radius)< 0 ? 0 : (units[index]->y - units[index]->weapon->radius);
    int leftBorder = (units[index]->x - units[index]->weapon->radius)< 0 ? 0 : (units[index]->x - units[index]->weapon->radius);
    int rightBorder = (units[index]->x + units[index]->weapon->radius)>gameMap.width ? (gameMap.width-1):(units[index]->x + units[index]->weapon->radius);
    int bottomBorder = (units[index]->y + units[index]->weapon->radius)>gameMap.height ? (gameMap.height - 1): (units[index]->y + units[index]->weapon->radius);
    
    GameBlock* currentBlock;
    std::vector <std::pair<Unit*, TeamEntity*>> enemiesList;
    std::vector <std::pair<Base*, TeamEntity*>> enemiesBases;
    Base* newBase = nullptr;
    Unit* newEnemy = nullptr;
    TeamEntity* currentEnemyTeam = nullptr;
   
    
    for(int i =  leftBorder; i <= rightBorder; i++){
        for(int j = topBorder; j <= bottomBorder; j++){
            if(units[index]->checkForAttack(i, j)){
                
                try{
                    currentBlock = gameMap.getBlock(j, i);
                }
                catch(BlockAccessException& ex){
                    Adapter a;
                    a.InfoStr(ex.message());
                    return false;
                }
                
                //get unit
                if(currentBlock->unitOnBlock!=nullptr){
                    for(auto itU = enemies.begin(); itU != enemies.end(); itU++){
                        newEnemy = (*itU)->getUnit(i, j);
                        if(newEnemy != nullptr){
                            enemiesList.push_back(std::make_pair(newEnemy, (*itU)));
                            break;
                        }
                    }
                   
                }
                //get base
                if(currentBlock->baseOnBlock != nullptr){
                    for(auto itU = enemies.begin(); itU != enemies.end(); itU++){
                       newBase = (*itU)->getBase(i, j);
                       if(newBase != nullptr){
                        enemiesBases.push_back(std::make_pair(newBase, (*itU)));
                           break;
                       }
                   }
                }
                
            }
        }
    }
    
    if(!(enemiesList.size() != 0 || enemiesBases.size() != 0)){
        std::cout<<"There are no enemies in your area!"<<std::endl;
        return false;
    }
    
    int baseOrUnit = -1; // 1 - units 2 - base
    if(enemiesList.size()!= 0 && enemiesBases.size() != 0){
        std::cout<<"You can attack base or units"<<std::endl;
        std::cout<<"Which one will be attacked? 0 - cancel 1 - units 2 - bases"<<std::endl;
        while(baseOrUnit >2 || baseOrUnit < 0){
            
            try{
                std::cin>>baseOrUnit;
                messageForLog <<"User input: "<<baseOrUnit<<std::endl;
                adapter.InfoStr(messageForLog.str());
            }

            catch(const std::istream::failure& ex){
                std::cout<<"User input fail. Cancel operation"<<std::endl;
                messageForLog <<"User input fail "<<index<<std::endl;
                adapter.InfoStr(messageForLog.str());
                adapter.InfoErrorCode(ex.code());
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                baseOrUnit = 0;
            }
            switch (baseOrUnit) {
                case 0:
                    return false;
                case 1:
                    baseOrUnit = 1;
                    break;
                case 2:
                    baseOrUnit = 2;
                    break;
                default:
                    break;
            }
        }
    }
    else{
        baseOrUnit = enemiesList.size() == 0?2:1;
    }
    
    if(baseOrUnit == 1){
        int input = -1;
           
           for(int i = 0; i < enemiesList.size(); i++){
               std::cout<<i+1<<") You can attack "<<enemiesList[i].first->type<<" standing on x = "<<enemiesList[i].first->x+1<<" y = "<<enemiesList[i].first->y+1<<std::endl;
              }
        std::cout<<"Which one will be attacked? 0 - Сancel "<<std::endl;
        while(1){
            
            try{
                 std::cin>>input;
                 messageForLog <<"User input: "<<index<<std::endl;
                 adapter.InfoStr(messageForLog.str());
            }
            catch(const std::istream::failure& ex){
                messageForLog <<"User input fail: "<<index<<std::endl;
                adapter.InfoStr(messageForLog.str());
                adapter.InfoErrorCode(ex.code());
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                index = 1;
                
            }
            
            if(input < 0 || input > enemiesList.size()){
                std::cout<<"Wrong command"<<std::endl;
            }
            else{
                break;
            }
        }
        if(input == 0){
            return false;
        }

        units[index]->attack(enemiesList[input-1].first);
        
        if(enemiesList[input-1].first->hitPoint <= 0){
            try {
                gameMap.getBlock(enemiesList[input-1].first->y, enemiesList[input-1].first->x)->unitOnBlock = nullptr;
            }
            catch(BlockAccessException& ex){
                Adapter a;
                a.InfoStr(ex.message());
                return false;
            }
        }
        currentEnemyTeam = enemiesList[input-1].second;
    }
    
    if (baseOrUnit == 2){
        int input = -1;
        
        for(int i = 0; i < enemiesBases.size(); i++){
            std::cout<<i+1<<") You can attack base on x = "<<enemiesBases[i].first->x+1<<" y = "<<enemiesBases[i].first->y+1<<std::endl;
        }
        std::cout<<"Which one will be attacked? 0 - Сancel "<<std::endl;
        while(1){
            try{
                 std::cin>>input;
                 messageForLog <<"User input: "<<index<<std::endl;
                 adapter.InfoStr(messageForLog.str());
            }
            catch(const std::istream::failure& ex){
                messageForLog <<"User input fail: "<<index<<std::endl;
                adapter.InfoStr(messageForLog.str());
                adapter.InfoErrorCode(ex.code());
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                index = 0;
                
            }
            if(input < 0 || input > enemiesBases.size()){
                std::cout<<"Wrong command"<<std::endl;
            }
            else{
                break;
            }
        }
        if(input == 0){
            return false;
        }
        units[index]->attack(enemiesBases[input-1].first);
        currentEnemyTeam = enemiesBases[input-1].second;
        if(enemiesBases[input-1].first->hitPoint <= 0){
            try{
                gameMap.getBlock(enemiesBases[input-1].first->y, enemiesBases[input-1].first->x)->baseOnBlock = nullptr;
            }
           catch(BlockAccessException& ex){
               Adapter a;
               a.InfoStr(ex.message());
               return false;
           }
            currentEnemyTeam->bases.pop_back();
            currentEnemyTeam->sizeBase--;
        }
        
    }
    currentEnemyTeam->update();
    return true;
}





//FOR LOAD
Unit* GameUnits::loadUnit(bool isNPC, int x, int y, int HP, int MP, int MR, int arm, char type){
    MagicallyResilientFactory f1;
    PhysicallyResilientFactory f2;
    Unit* newUnit;
    switch (type) {
        case 'R':
            newUnit = f1.createRogue();
            break;
        case 'S':
            newUnit = f2.createRogue();
            break;
        case 'W':
            newUnit = f1.createMage();
            break;
        case 'B':
            newUnit = f2.createMage();
            break;
        case 'P':
            newUnit = f2.createWarrior();
            break;
        case 'L':
            newUnit = f1.createWarrior();
            break;
        default:
           return nullptr;
           }
    newUnit->isNPC = isNPC;
    newUnit->x = x;
    newUnit->y = y;
    newUnit->hitPoint = HP;
    newUnit->manaPoint = MP;
    newUnit->magicResistance = MR;
    newUnit->armor = arm;
    return newUnit;
}


Base* GameUnits::loadBase(int x, int y, int HP, int maxUnit, int unitInBase){
    Base* base = new Base(x,y);
    base->hitPoint = HP;
    base->maxUnit = maxUnit;
    base->unitsInBase = unitInBase;
    return base;
};


NeutralObject* GameNeutralObjects::loadNO(int x, int y, int hp, char type){
    NeutralObject* newObj;
    Bonfire* newB;
    switch (type){
        case '!':
            newObj = new Bird;
            break;
        case '+':
            newObj = new Grave;
            break;
        case '@':
            newObj = new MrWitcher;
            break;
            
        case '-':
            newB = new Bonfire;
            newB->healing = 0;
            newB->type = '-';
            newObj = newB;
            break;
        case '&':
            newObj = new Bonfire;
            break;
        default:
            return nullptr;
    }
    newObj->x = x;
    newObj->y = y;
    newObj->hitPoint = hp;
    return newObj;
}

GameBases::GameBases(){
   sizeBase = 0;
   currentBase = -1;
}
//-------------------------NPC ACTION--------------------------//

void GameUnits::moveNPC(GameMap &gameMap, std::deque<TeamEntity*> teams){
    Unit* currentNPC = nullptr;
    Unit* nearestEnemy = nullptr;
    Unit* checkEnemy = nullptr;
    int distanseToNearest;
    int checkDistanseToNearest;
    GameBlock* currentBlock = nullptr;
    int visibilityRadius = 5;
    Adapter a;
    for(auto it = units.begin(); it !=  units.end(); it++){
        distanseToNearest = -1;
        nearestEnemy = nullptr;
        currentNPC = (*it);
        int topBorder = (currentNPC->y - visibilityRadius)< 0 ? 0 : (currentNPC->y - visibilityRadius);
        int leftBorder = (currentNPC->x - visibilityRadius)< 0 ? 0 : (currentNPC->x - visibilityRadius);
        int rightBorder = (currentNPC->x + visibilityRadius)>gameMap.width ? (gameMap.width-1): (currentNPC->x + visibilityRadius)-1;
        int bottomBorder = (currentNPC->y + visibilityRadius)>gameMap.height ? (gameMap.height - 1): (currentNPC->y + visibilityRadius)-1;
        for(int i =  leftBorder; i <= rightBorder; i++){
               for(int j = topBorder; j <= bottomBorder; j++){
                   
                   try{
                   currentBlock = gameMap.getBlock(j, i);
                   }
                  catch(BlockAccessException& ex){
                      Adapter a;
                      a.InfoStr(ex.message());
                  }
                   
                   
                   if(currentBlock->unitOnBlock!=nullptr ){
                       checkEnemy = currentBlock->unitOnBlock;
                       if(checkEnemy->isNPC == false){
                           checkDistanseToNearest  = abs(currentNPC->x - checkEnemy->x) + abs(currentNPC->y - checkEnemy->y);//Manhattan distance
                           if(checkDistanseToNearest < distanseToNearest ||distanseToNearest == -1){
                               distanseToNearest = checkDistanseToNearest;
                               nearestEnemy = checkEnemy;
                           }
                       }
                       else{
                           continue;
                       }
                   }
               }
        }
        
        if(nearestEnemy != nullptr){
            if(currentNPC->checkForAttack(nearestEnemy->x, nearestEnemy->y)){
                std::cout<<"NPC "<<currentNPC->type<<" standing on("<<currentNPC->x+1<<","<<currentNPC->y+1<<") attack "<<nearestEnemy->type<<" standing on("<<nearestEnemy->x+1<<","<<nearestEnemy->y+1<<")"<<std::endl;
            
                currentNPC->attack(nearestEnemy);
                if(nearestEnemy->hitPoint <= 0){
                    try{
                    gameMap.getBlock(nearestEnemy->y, nearestEnemy->x)->unitOnBlock = nullptr;
                    }
                   catch(BlockAccessException& ex){
                       Adapter a;
                       a.InfoStr(ex.message());
                       return;
                   }
                    for(auto it = teams.begin(); it != teams.end(); it++){
                        (*it)->update();
                    }
                }
            }
            else{
                std::cout<<"NPC "<<currentNPC->type<<" standing on("<<currentNPC->x+1<<","<<currentNPC->y+1<<") moving"<<std::endl;
                int oldX = currentNPC->x;
                int oldY = currentNPC->y;
                int x = (nearestEnemy->x - currentNPC->x == 0)?0:((nearestEnemy->x - currentNPC->x) < 0?-1:1);
                int y = (nearestEnemy->y - currentNPC->y == 0)?0:((nearestEnemy->y - currentNPC->y) < 0?-1:1);
                
                if( x!= 0 & y != 0 ){
                    if(rand()%2 == 1){
                        if(!(currentNPC->move(x, 0, gameMap))){
                            currentNPC->move(0, y, gameMap);
                        }
                        
                    }
                    else{
                        if(!(currentNPC->move(0, y, gameMap))){
                            currentNPC->move(x, 0, gameMap);
                        }
                    }
                   
                }
                else if(x != 0){
                    currentNPC->move(x, 0, gameMap);
                }
                else{//y != 0
                    currentNPC->move(0, y, gameMap);
                }
                a.InfoMove(currentNPC, oldX, oldY);
                if(currentNPC->hitPoint <= 0){
                    try{
                    gameMap.getBlock(currentNPC->y, currentNPC->x)->unitOnBlock = nullptr;
                    }
                   catch(BlockAccessException& ex){
                       Adapter a;
                       a.InfoStr(ex.message());
                       return;
                   }
                    units.erase(it);
                }
            }
        }else{
            std::cout<<"NPC "<<currentNPC->type<<" standing on("<<currentNPC->x+1<<","<<currentNPC->y+1<<") decided to stay idle"<<std::endl;
            
        }
    
    }
}
//-------------------------------------------------------------//
std::istream& operator >>(std::istream& os, TeamEntity& cont){
    int a;
    os>>cont.isActive>>cont.isDefeated>>a;
    cont.type = (typeU)a;
    int x;
    int y;
    
    //load units out of base
    int unitSize;
    int indexCurrentU;
       
    int HP;
    int MP;
    int MR;
    int arm;
    char type;
    bool isNPC;
    os>>unitSize>>indexCurrentU;
    cont.size = unitSize;
    cont.units.clear();
    cont.currentUnit = indexCurrentU;
    for(int i = 0; i < unitSize; i++){
        os>>isNPC>>x>>y>>HP>>MP>>MR>>arm>>type;
        cont.units.push_back(cont.loadUnit(isNPC, x,y,HP,MP,MR,arm,type));
    }
    //load bases and units in base
    int baseCount;
    int indexCurB;
    int maxUnit;
    int unitInBase;
    int unitContSize;
    os>>baseCount>>indexCurB;
    cont.currentBase = indexCurB;
    cont.bases.clear();

    for(int i = 0; i < baseCount; i ++){
        os>>x>>y>>HP>>maxUnit>>unitInBase>>unitContSize;
        cont.bases.push_back(cont.loadBase(x, y, HP, maxUnit, unitInBase));
        cont.bases[i]->units.clear();
        for(int j = 0; j < unitContSize; j++){
            os>>isNPC>>x>>y>>HP>>MP>>MR>>arm>>type;
            cont.bases[i]->units.push_back(cont.loadUnit(isNPC, x,y,HP,MP,MR,arm,type));
          
        }
    }
    return os;
}

std::ostream& operator <<(std::ostream& os, const TeamEntity& cont){
   

    os<<cont.isActive<<" "<<cont.isDefeated<<" "<<cont.type<<" ";
    os<<cont.size<<" "<<cont.currentUnit<<std::endl;
    for(int i = 0; i < cont.size; i++){
        os<<*(cont.units[i]);
    }

    os<<cont.sizeBase<<" "<<cont.currentBase<<std::endl;
    for(int i = 0; i < cont.sizeBase; i++){
        os<<*(cont.bases[i]);
    }
    return os;
}

std::ostream& operator <<(std::ostream& os, const GameNeutralObjects& cont){
  //  os<<"NO"<<std::endl;
       
    os<<cont.sizeNO<<std::endl;
    for(int i = 0; i < cont.sizeNO; i++){
        os<<*(cont.neutralObjects[i]);
    }
    return os;
}

std::istream& operator >>(std::istream& os, GameNeutralObjects& cont){
    int count;
    int x;
    int y;
    int hp;
    char type;
    os>>count;
    cont.neutralObjects.clear();
    for(int i = 0; i < count; i++){
        os>>x>>y>>hp>>type;
        cont.neutralObjects.push_back(cont.loadNO(x, y, hp, type));
    }
    return os;
}



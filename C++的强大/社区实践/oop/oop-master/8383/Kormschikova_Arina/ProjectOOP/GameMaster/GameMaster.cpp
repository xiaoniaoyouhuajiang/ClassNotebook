
#include <iostream>

#include "GameMaster.h"
#include "Map.h"
#include "Base.h" 
#include "Units.h"
#include "GameVisualization.h"
#include "GameBlock.h"
#include "NeutralObject.h"


void GameMaster::setMap(){
    int width, height;
    do{
        width = 9;
        height = 9;
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
    
    map->getBlock(0,5)->objectOnBlock = new MrWitcher;
    map->getBlock(6, 2)->objectOnBlock = new Bonfire;
    map->getBlock(7, 7)->objectOnBlock = new Grave;
    map->getBlock(2, 7)->objectOnBlock = new Bird;
}


void GameMaster::setBase(){
    int x, y;
    do{

        std::cout<<"Enter coord for base: ";
        std::cin>>x>>y;

    } while(!(x > 0 && y > 0 && y <= map->getHeight() && x <= map->getWidth() && map->getBlock(y-1, x-1)->isEmpty()));
    x--;
    y--;
    base = new Base(x, y);
    this->map->getBlock(y, x)->baseOnBlock = new Base(x, y);
    base->createUnit('R');
//    base->createUnit('S');
    
}

void GameMaster::baseControl(){
    if(this->base == nullptr){
        setBase();
    }
    base->baseUpdate();
    char input;
    Unit* newUnit;
    do{
        std::cout<<"Enter command for base 'c' - Create unit, 's' - select unit: "<<std::endl;
        std::cin>>input;
        std::cout<<std::endl;
        switch (input) {
            case 'c':
                base->createUnit();
                break;
            case 's':
                newUnit = base->getUnit();
                if(newUnit == nullptr){
                    continue;
                }
                else{
                    input = 'w';
                    units.addUnit(newUnit, base->x, base->y, *map);
                    break;
                }
            default:
                break;
        }
        
    }while(input != 'w');
}


void GameMaster::gameCycle() {
    char input;
    setMap();
    update(*map);
    baseControl();
    int index = 0;
    int deathCheck = 0;
    do {
        update(*map);
        std::cout << "Enter command: ";
        std::cin >> input;
        std::cout<<std::endl;
        switch (input) {
            case 'w':
                deathCheck = units.moveUnit(0, -1, index, *map);
                break;
            case 's':
                deathCheck = units.moveUnit(0, 1, index, *map);
                break;
            case 'd':
                deathCheck = units.moveUnit(1, 0, index, *map);
                break;
            case 'a':
                deathCheck = units.moveUnit(-1, 0, index, *map);
                break;
            default:
                break;
                
        }
        if(deathCheck){
            map->getBlock(units.units[index]->y, units.units[index]->x )->unitOnBlock = nullptr;
            units.units.pop_back();
            baseControl();
        }
    } while (input != 'p');
}

GameUnits::GameUnits() {
      size = 0;
}

void GameUnits::addUnit(Unit *unit, int x, int y, GameMap &gameMap){
    this->size++;
    units.push_back(unit);
    units[0]->x = x;
    units[0]->y = y;
    gameMap.map[y][x].setUnit(unit);
}


Unit* GameUnits::getUnit(int x, int y) {
    for (int i = 0; i < size; i++) {
        if (units[i]->x == x && units[i]->y == y) return units[i];
    }
    
    return nullptr;
}


//------------------------------------//
bool GameUnits::moveUnit(int x, int y, int index, GameMap &gameMap) {
    units[index]->move(x, y, gameMap);
    if(units[index]->hitPoint < 1){
        return 1;
    }
    return 0;
};

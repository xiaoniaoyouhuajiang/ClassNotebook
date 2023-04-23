#include <iostream>
#include "Map.h"
#include "GameBlock.h"
#include "Exeptions.h"
#include "Logger.h"
GameMap::GameMap(int height, int width){
    
    this->height = height;
    this->width = width;
    //map = new GameBlock* [height];
    map.resize(height);
    
    for(int i = 0; i < height; i++){
        map[i].resize(width);
    }
}

GameMap::GameMap(){
    this->height = 0;
    this->width = 0;
    
}




GameMap::~GameMap(){
}

int GameMap::getWidth(){
    return this->width;
}

int GameMap::getHeight(){
    return this->height;
}

GameBlock* GameMap::getBlock(int y, int x){
    if(y >= 0 && x >= 0 && y < this->height && x < this->width){
        return &(map[y][x]);
    }
    else{
        throw BlockAccessException(x, y);
        return nullptr;
    }
}

std::ostream& operator <<(std::ostream& os, const GameMap& map){
    os<<map.height<<" "<<map.width<<std::endl;
  
    for(int i = 0; i < map.height; i++){
        for(int j = 0; j < map.width; j++){
            os<<map.map[i][j].landscape->typeForSave<<" ";
        }
        os<<std::endl;
    }
    return os;
}

std::istream& operator >>(std::istream& os,  GameMap& map){
    int height;
    int width;
    int type;
    os>>height>>width;
    
    map.height = height;
    map.width = width;
    map.map.clear();
    map.map.resize(height);
    
    for(int i = 0; i < height; i++){
        map.map[i].clear();
        map.map[i].resize(width);
    }
    
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            os>>type;
            map.map[i][j].setLandscape(type);
        }
    }
    return os;
}


//
//GameMap::GameMap(const GameMap&other){
//    this->height = other.height;
//    this->width = other.width;
//    this->map = new GameBlock* [height];
//    for(int i = 0; i < height; i++){
//        this->map[i] = new GameBlock [width];
//    }
//    for(int i = 0; i < height; i++){
//        for(int j = 0; j < width; j++){
//            this->map[i][j] = other.map[i][j];
//        }
//    }
//};

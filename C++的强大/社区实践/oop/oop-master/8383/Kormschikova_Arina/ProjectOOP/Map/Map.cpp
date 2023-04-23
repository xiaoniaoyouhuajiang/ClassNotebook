#include <iostream>
#include "Map.h"
#include "GameBlock.h"

GameMap::GameMap(int height, int width){
    
    this->height = height;
    this->width = width;
    map = new GameBlock* [height];
    for(int i = 0; i < height; i++){
        map[i] = new GameBlock [width];
    }
}

GameMap::GameMap(){
    this->height = 0;
    this->width = 0;
    map = nullptr;
}




GameMap::~GameMap(){
    for(int i = 0; i < height; i++){
        delete [] map[i];
    }
    delete [] map;
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
    return &(map[0][0]);
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

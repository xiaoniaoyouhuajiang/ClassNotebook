#include "Gamefield.h"
#include "Unit.h"
#include "TerrainProxy.h"
#include "RiverProxy.h"
#include "GrassProxy.h"
#include "StoneProxy.h"
#include "Healing.h"
#include "Mine.h"
#include "Portal.h"
#include <cstdlib>

GameField::GameField(int width, int height)
: width_(width), height_(height), countObj(0)
{
    initialise();
    createMap();
}


void GameField::initialise()
{
    gridLogic = new pTerrain* [height_];
    gridView = new int*[height_];
    for (int i = 0; i < this->height_; i++){
        gridLogic[i] = new pTerrain[width_];
        gridView[i] = new int[width_];
        for (int j = 0; j < width_; j++){
           gridLogic[i][j] = nullptr;
           gridView[i][j] = 0;
        }
    }
}


void GameField::addObj(Obj obj){
    int cellX = obj->x_;
    int cellY = obj->y_;

    if (obj->isHero()){
        openArround(cellX, cellY);
    }
    gridLogic[cellX][cellY]->addObj(obj);

}


void GameField::deleteObj(Obj tmp)
{
  if(tmp != nullptr) delete tmp;
}


bool GameField::move(Unit* unit, int x, int y){
    if (x < 0 || y < 0 || x >= height_ || y >= width_)
         return false;
    // Смотрим в какой клетке находимся.
    int oldCellX = unit->x_;
    int oldCellY = unit->y_;
    // Смотрим в какую клетку перемещаемся.
    int cellX = x;
    int cellY = y;

    if (!gridLogic[cellX][cellY]->isMovement())
        return false;

    //Никуда не переместились
    if (oldCellX == cellX && oldCellY == cellY)
        return false;
    unit->x_ = x;
    unit->y_ = y;

    gridLogic[oldCellX][oldCellY]->removeObj();

   // beep();
    addObj(unit);

    return true;
}


void GameField::openArround(int x, int y)
{
  for (int curX = x-1; curX < (x+2); curX++){
    for (int curY = y-1; curY < (y+2); curY++){
      if (!(curX < 0 || curY < 0 || curX > this->width_ || curY > this->height_) && (curX != x || curY != y))
          gridLogic[curX][curY]->open();
    }
  }
}



void GameField::update()
{
    for (int i = 0; i < height_; i ++){
        for (int j = 0; j < width_; j++) {
            gridView[i][j] = gridLogic[i][j]->getAnimation();
        }
    }
}



void GameField::createMap(){
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
           if ( ((j > 5 && j < 7)||(j > 29 && j <35) ) && (i < 10 || (i>25 && i < 36))  )
            gridLogic[i][j] = new RiverProxy(i,j, true);
          // gridLogic[i][j] = new RiverProxy(i,j);
          else if (rand()%25+1 == 7)
            gridLogic[i][j] = new StoneProxy(i,j, true);
          // gridLogic[i][j] = new StoneProxy(i,j);
           else
            gridLogic[i][j] = new GrassProxy(i,j, true);
           // gridLogic[i][j] = new GrassProxy(i,j);
        }
    }


    for (int i = 0; i < height_; i++) {
        for (int j = 0;j< width_; j++) {
            if (gridLogic[i][j]->isMovement()){
                if (rand()%100 + 1 == 5)
                    addObj(new Healing(this,i,j));
                else if(rand()%100 + 1 == 7)
                    addObj(new Mine(this,i,j));
                else if (rand()%100 + 1 == 8){
                    Portal* t = new Portal(this,i,j);
                    int x,y;  x = rand()%height_+1; y = rand()%width_+1;
                    t->addPlace(x, y);
                    addObj(t);
                }
                else {
                    continue;
                }
            }
        }
    }

}


int GameField::getWidth(){
    return width_;
}

int GameField::getHeight(){
    return height_;
}



GameField::~GameField(){
    for (int i = 0; i < height_; i++){
        for (int j = 0; j < width_; j++){
            if(gridLogic[i][j])
                delete gridLogic[i][j];
        }
    }
    delete [] gridLogic;
}

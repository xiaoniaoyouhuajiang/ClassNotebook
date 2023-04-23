#include "Terrain.h"
#include "GameObj.h"
#include <typeinfo>
#include "TerrainTexture.h"
#include "Unit.h"
#include "Healing.h"
#include "Mine.h"
#include "Portal.h"


Terrain::Terrain(int x, int y)
 : cellX(x), cellY(y) {}


Obj Terrain::getObj()
{
   return obj;
}


void Terrain::removeObj(){
  if (this->obj)
  {
       setObj(nullptr);
  }
}


bool Terrain::addObj(Obj obj_)
{
   if (this->obj==nullptr){
      setObj(obj_);
      return true;
    }
   if (obj_->isHero() && obj!=nullptr && obj->isNeutral())
   {
      Unit* hero = (Unit*)obj_;
      if (typeid(*obj) == typeid(Healing)){
         Healing* tmp = (Healing*)obj;
         (*hero) += (*tmp);
         deleteObj(); setObj(hero);
      }
      if (typeid(*obj) == typeid(Mine)){
         Mine* tmp = (Mine*)obj;
         (*hero) += (*tmp);
         deleteObj(); setObj(hero);
      }
      if (typeid(*obj) == typeid(Portal)){
         Portal* tmp = (Portal*)obj;
         (*hero) += (*tmp);
      }
      return true;
   }
   else
      return false;
}


int Terrain::getAnimation(){
    if (state == OPEN){
      if (obj != nullptr)
         return obj->getAnimation();
      else if (state == OPEN)
         return texture->getTexture();
    }
    return 0;
}

Unit* Terrain::getUnit(){
    if (obj){
        if (obj->isHero())
        {
            Unit* hero = (Unit*)obj;
            return hero;
        }
    }
    return nullptr;
}


void Terrain::setObj(Obj obj_)
{
  this->obj = obj_;
  if(obj){
      if (obj->isHero())
           open();
  }
}



// ДОБАВИТЬ ОТРИСОВКУ В
// ПОЛЕ ДЛЯ ВЫВОДА

void Terrain::open()
{
    this->state = OPEN;
}

void Terrain::deleteObj(){
    if (this->obj){
        delete obj;
        removeObj();
    }
}


AttributeTerrain::~AttributeTerrain(){
    if (obj)
        delete obj;
    if (texture)
        delete texture;
}

Terrain::~Terrain()
{}

#include "River.h"
#include "GameObj.h"
#include "RiverTexture.h"
#include "Unit.h"


bool River::addObj(Obj obj_)
{
   if (this->obj==nullptr){
      setObj(obj_);
      if (obj_->isHero()){
          this->affect();
      }
      return true;
    }
 /*  if (obj_->isHero() && obj!=nullptr && obj->isNeutral())
   {
      if (typeid(*obj) == typeid(Healing)){
         Healing* ch = (Healing*)obj;
         (*obj_) += (*ch);
      }
      if (typeid(*obj) == typeid(Mine)){
         Mine* ch = (Mine*)obj;
         (*obj_) += (*ch);
      }
      setObj(obj_);
   }
   else
      return;
*/
   return false;
}



bool River::isMovement()
{
    if (obj && obj->isNeutral()) return true;
    if (obj == nullptr) return true;
    return false;
}


int River::getMovementCost()
{
    return RIVER_COST;
}


River::River(int x, int y) //: movementCost(GRASS_COST),  moveable(GRASS_MOVEABLE),
 : Terrain(x,y)
{
    if (texture == nullptr){
        texture = new RiverTexture;
    }
    this->obj = nullptr;
    this->state = CLOSED;
}



void River::affect()
{
  if (obj){
      Unit* unit_tmp = (Unit*)obj;
      unit_tmp->affectBlock();
      //лучше Unit::BLOCK_ATTACK
  }
}


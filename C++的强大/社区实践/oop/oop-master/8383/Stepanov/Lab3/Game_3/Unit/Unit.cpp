//
//  Unit.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Unit.hpp"
   
   void Unit::Attach(IObserver *observer)  {
       observers.push_back(observer);
   }

   void Unit::Detach(IObserver *observer) {
      observers.remove(observer);
   }

   void Unit::Notify() {
      std::list<IObserver *>::iterator iterator = observers.begin();
      
       while (iterator != observers.end()) {
        (*iterator)->Update(this);
        ++iterator;
           
           
      }
    }
   
void  Unit::hit (Field *field, int x, int y){}
void  Unit::motion (){}
void  Unit::setName (char unitNumberInName){}



   
   char * Unit::getName (){
       return name;
   }
   
   void Unit::setXY(int x, int y){
       this-> x = x;
       this-> y = y;
   }
   
   int Unit::getX(){
       return x;
   }
   
   int Unit::getY(){
       return y;
   }
   
   void Unit::incHealth (int n){
       
       health.inc(n);
       
       if (health.getPoint() < 0){
           Notify();
       }
   }

void Unit::incArmor (int n){
    
    armor.inc(n);
    
    if (armor.getPoint() <= 0){
        health.inc(armor.getPoint());
        armor.setPoint(0);
        
    }
}

void Unit::incAttack (int n){
    
    attack.inc(-1);
    
    if (attack.getPoint() < 0){
        attack.setPoint(0);
    }
}

//
//  Unit.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Unit_hpp
#define Unit_hpp

#include <list>

#include "Point.hpp"
#include "ISubject.hpp"
#include "UnitID.hpp"
#include "IObserver.hpp"


class Field;

class Unit: public ISubject{

 public:
    
    Point health;
    Point armor;
    Point attack;
    int x;
    int y;
    bool attackIsBlocked = false;
    
    std::list<IObserver *> observers;
    
    char name[3];
    UnitID *uid;
    
    
    void Attach(IObserver *observer) override;

    void Detach(IObserver *observer) override;

    void Notify() override;
    
 
    void virtual hit (Field *field, int x, int y);
    void virtual motion ();
    void virtual setName (char unitNumberInName);
    
    char *getName ();
    
    void setXY(int x, int y);
    
    int getX();
    
    int getY();
    
    void incHealth (int n);
    void incArmor (int n);
    void incAttack (int n);
    

};


#endif /* Unit_hpp */

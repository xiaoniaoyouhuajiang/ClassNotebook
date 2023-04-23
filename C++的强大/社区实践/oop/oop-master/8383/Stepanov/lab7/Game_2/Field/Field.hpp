//
//  Field.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Field_hpp
#define Field_hpp

#include <iostream>
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()

#include "Cell.hpp"
#include "ConcreteGround.hpp"
#include "ConcreteBush.hpp"
#include "ConcreteDeepPuddel.hpp"

#include "FieldSnapshot.hpp"



class Field {
    
    int height, width;
    Cell ** place;
    
    int busyCells = 0;
    int maxBusyCells;
    
public:
    
    Field ();
 
    ~Field ();
    
    bool createField(int width, int height);
    
    int checkXY (int x, int y);

    int whatInCell (int x, int y);

    bool replaceUnit(int fromX, int fromY, int toX, int toY);
    
    void setBase(std::string b, int x, int y);
    void setUnit (Unit* u, int x, int y);
    void setNeutralObject (NeutralObject *n, int x, int y);

    Unit *getUnit(int x, int y);
    std::string getBase(int x, int y);
    Landscape * getLandscape (int x, int y);
    NeutralObject * getNeutralObject (int x, int y);
    int getWidth ();
    int getHeight ();
    
    FieldSnapshot* saveField ();
       
    void restore (FieldSnapshot* snap);
    
    
    
};

#endif /* Field_hpp */

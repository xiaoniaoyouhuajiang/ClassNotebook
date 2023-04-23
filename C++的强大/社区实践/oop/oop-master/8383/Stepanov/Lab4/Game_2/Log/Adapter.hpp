//
//  Adapter.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Adapter_hpp
#define Adapter_hpp

#include <string>


class Adapter{
    
public:
   
    std::string adaptMove (char name[3], int x, int y, int toX, int toY);
    std::string adaptHit (char name[3], int x, int y, int toX, int toY);
    std::string adaptSpawn (char name[3], int x, int y);
    std::string adaptUnitAttack (char name1[3], int power, char name2[3], int armor, int health);
    std::string deletUnit (char name[3]);
    std::string adaptLandscape (char name);
    std::string adaptUnitWithObject (char nameUnit[3], int h, int a, int p, char nameObject[3]);
    std::string isComplited (bool b);
};

#endif /* Adapter_hpp */

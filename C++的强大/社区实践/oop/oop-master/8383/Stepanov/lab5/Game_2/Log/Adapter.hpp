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
   
    std::string adaptMove (std::string name, int x, int y, int toX, int toY);
    std::string adaptHit (std::string name, int x, int y, int toX, int toY);
    std::string adaptSpawn (std::string name, int x, int y);
    std::string adaptUnitAttack (std::string name1, int power, std::string name2, int armor, int health);
    std::string deletUnit (std::string name);
    std::string adaptLandscape (char name);
    std::string adaptUnitWithObject (std::string nameUnit, int h, int a, int p, char nameObject[3]);
    std::string isComplited (bool b);
};

#endif /* Adapter_hpp */

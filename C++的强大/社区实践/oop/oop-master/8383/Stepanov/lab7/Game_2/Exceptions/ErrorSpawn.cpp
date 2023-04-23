//
//  ErrorSpawn.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 18.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ErrorSpawn.hpp"

ErrorSpawn::ErrorSpawn(char base, char unit){
    this->base = base;
    this->unit = unit;
}
  
char ErrorSpawn::getBase (){return base;}
char ErrorSpawn::getUnit (){return unit;}
  
void ErrorSpawn::writeErr (){
    
    std::cout << "Нельзя базой  В" << base << " заспавинть юнита " << unit << std::endl;
}

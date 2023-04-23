//
//  WrongMotion.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 18.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "WrongMotion.hpp"

WrongMotion::WrongMotion (std::string name){
    this->name = name;
}

std::string WrongMotion::getMotion (){return name;}
  
void WrongMotion::writeErr (){
    
    std::cout << "Комманды " << name << " не существует" << std::endl;
}

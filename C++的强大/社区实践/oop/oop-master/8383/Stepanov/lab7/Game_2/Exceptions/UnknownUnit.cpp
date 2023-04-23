//
//  UnknownUnit.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 18.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "UnknownUnit.hpp"

UnknownUnit::UnknownUnit(std::string name){
    this->name = name;
}

std::string UnknownUnit::getName(){return name;}

void UnknownUnit::writeErr(){
    std::cout << "Юнит с ником \"" << name << "\" не найден" << std::endl;
}

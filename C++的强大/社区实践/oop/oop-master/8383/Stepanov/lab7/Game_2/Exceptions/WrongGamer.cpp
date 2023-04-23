//
//  WrongGamer.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 18.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "WrongGamer.hpp"

WrongGamer::WrongGamer (std::string name){
    
    this->name = name;
}

WrongGamer::WrongGamer (char name){
    
    this->name.push_back('B');
    this->name.push_back(name);
}
 
std::string WrongGamer::getName(){return name;}
 
void WrongGamer::writeErr (){
    
    std::cout << "Нельзя использовать  \"" << name << "\", так как он принадлежит другому игроку" << std::endl;
    
}

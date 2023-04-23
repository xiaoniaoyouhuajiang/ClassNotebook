//
//  ErrorSpec.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 18.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ErrorSpec.hpp"

ErrorSpec::ErrorSpec(std::string name){
    
    type = 1;
    this->name = name;
}
ErrorSpec::ErrorSpec(int num){
    type = 0;
    this->num = num;
}
  
std::string ErrorSpec::getName (){
    if (type) {
        return name;
    }
    return nullptr;
}

int ErrorSpec::getNum(){
    
    if (type){
        return -1;
    }
    return num;
    
}
  
void ErrorSpec::writeErr(){
    
    
    if (type) {
        
        std::cout << "У юнита " << name << " нет спец способности" << std::endl;
    } else {
        
        std::cout << "Спец способность можно применить через " << num << " шагов" << std::endl;
    }
}

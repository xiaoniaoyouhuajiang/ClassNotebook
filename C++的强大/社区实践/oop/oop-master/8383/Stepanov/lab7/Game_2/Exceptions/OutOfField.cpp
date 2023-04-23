//
//  OutOfField.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 18.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "OutOfField.hpp"

OutOfField::OutOfField(int x, int y){
    this->x = x;
    this->y = y;
}


int OutOfField::getX(){return x;}

int OutOfField::getY(){return y;}

void OutOfField::writeErr(){
    
    std::cout << "Нельзя перейти в клетку x = " << x << " y = " << y << std::endl;
}

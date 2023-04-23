//
//  FieldSnapshot.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 02.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "FieldSnapshot.hpp"

FieldSnapshot::FieldSnapshot(int height, int width, char ** place, int busyCells, int maxBusyCells){
    
    this->height = height;
    this->width = width;
    this->place = place;
    this->busyCells = busyCells;
    this->maxBusyCells = maxBusyCells;
}

FieldSnapshot::FieldSnapshot(){}

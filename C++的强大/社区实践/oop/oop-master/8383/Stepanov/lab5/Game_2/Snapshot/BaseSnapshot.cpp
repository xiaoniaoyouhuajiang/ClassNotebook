//
//  BaseSnapshot.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 02.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "BaseSnapshot.hpp"

BaseSnapshot::BaseSnapshot(std::vector<std::string> names,
                           std::vector<int> h,
                           std::vector<int> a,
                           std::vector<int> p,
                           std::vector<bool> blocAtt,
                           std::vector<int> ux,
                           std::vector<int> uy,
                           
                           int numberUnit,
                           int countUnit,
                           int x,
                           int y,
                           int concretCountUnit[3],
                           std::string name){
    
    this->names = names;
    this->h = h;
    this->a = a;
    this->p = p;
    this->blocAtt = blocAtt;
    this->ux = ux;
    this->uy = uy;
    
    this->numberUnit = numberUnit;
    this->countUnit = countUnit;
    this->x = x;
    this->y = y;
    this->concretCountUnit[0] = concretCountUnit[0];
    this->concretCountUnit[1] = concretCountUnit[1];
    this->concretCountUnit[2] = concretCountUnit[2];
    this->name = name;

    
    this->numberUnit = numberUnit;
}

BaseSnapshot::BaseSnapshot(){}

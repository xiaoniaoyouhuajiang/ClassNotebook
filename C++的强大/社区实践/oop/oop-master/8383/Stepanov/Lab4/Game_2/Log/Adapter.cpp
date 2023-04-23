//
//  Adapter.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Adapter.hpp"

std::string Adapter::adaptMove (char name[3], int x, int y, int toX, int toY){
    
    std::string s;
    
    
    s += "Перемещение юнита ";
    s += name;
    s += " из ";
    s += std::to_string(x);
    s += " ";
    s += std::to_string(y);
    s += " в ";
    s += std::to_string(toX);
    s += " ";
    s += std::to_string(toY);
    
    return s;
}

std::string Adapter::adaptHit (char name[3], int x, int y, int toX, int toY){
    
    std::string s;
    
    s += "Юнит ";
    s += name;
    s += " атакует из точки ";
    s += std::to_string(x);
    s += " ";
    s += std::to_string(y);
    s += " в направлении ";
    s += std::to_string(toX);
    s += " ";
    s += std::to_string(toY);
    
    return s;
}

std::string Adapter::adaptSpawn (char name[3], int x, int y){
    
    std::string s;
    
    s += "Создание юнита ";
    s += name;
    s += " в точке ";
    s += std::to_string(x);
    s += " ";
    s += std::to_string(y);
    
    return s;
}

std::string  Adapter::adaptUnitAttack (char name1[3], int power, char name2[3], int armor, int health){
    
    std::string s;
    
    s += "Юнит ";
    s += name1;
    s += " с силой ";
    s += std::to_string(power);
    s += " атакует юнита ";
    s += name2;
    s += " с броней ";
    s += std::to_string(armor);
    s += " и здоровьем ";
    s += std::to_string(health);
    
    return s;
}

std::string Adapter::deletUnit (char name[3]){
    
    std::string s;
    
    s += "Удаление юнита ";
    s += name;
    
    return s;
}

std::string Adapter::adaptLandscape (char name){
    
    std::string s;
    
    s += "Ландшафт в точке перемещения \"";
    s += name;
    s += name;
    s += '\"';
    
    return s;
}

std::string Adapter::adaptUnitWithObject (char nameUnit[3], int h, int a, int p, char nameObject[3]){
    
    std::string s;
    
    s += "";
    s += nameUnit;
    s += "(h: ";
    s += std::to_string(h);
    s += ", a: ";
    s += std::to_string(a);
    s += ", p: ";
    s += std::to_string(p);
    s += ") взаимодействует с ";
    s += nameObject;
    
    return s;
    
}



std::string Adapter::isComplited (bool b){
    
    if (b)
        return "Действие совершено";
    else
        return "Действие не  совершено";
}


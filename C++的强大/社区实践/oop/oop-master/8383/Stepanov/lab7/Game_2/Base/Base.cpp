//
//  Base.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Base.hpp"



    Unit* Base::createUnit(int whatUnit, int uniqNum) {

        ConcreteUnitShooter sho;
        ConcreteUnitRunner run;
        ConcreteUnitSmoker smo;

        Unit *u = nullptr;

        if (whatUnit == 0) u = smo.CreateUnit(uniqNum, isProtect);

        else if (whatUnit == 1) u  = sho.CreateUnit(uniqNum, isProtect);

        else if (whatUnit == 2) u = run.CreateUnit(uniqNum, isProtect);

        else return nullptr;

        u->uid = flyFactory.getUnitID(whatUnit);
        
          

        return u;

    }

    
    Base::~Base () {

        for (int i = 0; i < toDelet.size(); i++){
            delete toDelet[i];
        }
        
        
        for (int i = 0; i < 9; i++){
            if (units[i]) {
                delete units[i];
            }
        }
    }

//    ++++++++++++++++++++++++++++++++++++++
    
    
    void Base::Update(Unit *unit) {
        std::cout << unit->getName() << " убит" << std::endl;

        field->setUnit(nullptr, unit->getX(), unit->getY());

        for (int i = 0; i < 9; i++){

            if (units[i] == unit) {
                units[i] = nullptr;
                break;
            }
        }

        toDelet.push_back(unit);
        countUnit--;
        
        log->write(adapter.deletUnit(unit->getName()));

    }

    
    std::string Base::getName () {
        return name;
    }
    
    
    Base::Base (int i, int x, int y, Field *field, ProxyLog *log, bool isProtect, IObserver* game) {
       
        this->x = x;
        this->y = y;
        concretCountUnit[0] = i - 2;
        concretCountUnit[1] = i - 2;
        concretCountUnit[2] = i - 2;
        
        this->isProtect = isProtect;
        this->game = game;
        
        name.push_back('B');
 
        if (x > y) {
            name.push_back('1');

        } else {
            name.push_back('2');
        }
        
        this->field = field;
        field->setBase(this->name, x, y);
        
        this->log = log;
            
    }
    
    bool Base::setFirstUnits (Field *field) {

        int arr[6] = {0, 1, 1, 2, 2, 2};

        for (int i = 0; i < 6; i++) {
            
            concretCountUnit[arr[i]] += 2;
            units[i] = createUnit(arr[i], concretCountUnit[arr[i]]+'0');

            units[i]->Attach(this);


        }
        
        units[0]->Attach(game);

        if (x > y) {

            units[0]->setXY(x-1, 1);
            units[1]->setXY(x-2, 0);
            units[2]->setXY(x  , 2);
            units[3]->setXY(x-1, 3);
            units[4]->setXY(x-2, 2);
            units[5]->setXY(x-3, 1);



        } else {


            units[0]->setXY(1, y-1);
            units[1]->setXY(0, y-2);
            units[2]->setXY(2, y);
            units[3]->setXY(3, y-1);
            units[4]->setXY(2, y-2);
            units[5]->setXY(1, y-3);


        }

        for (int i = 0; i < 6; i++){
            field->setUnit(units[i], units[i]->getX(), units[i]->getY());
            units[i]->setLogOut(log);
        }

        countUnit = 6;





        return true;

    }

    Unit* Base::getUnit (int i) {

        return units[i];
    }

    Unit* Base::findUnit (std::string name){

        for (int i = 0; i < 9; i++) {

            if (units[i] && units[i]->name[0] == name[0] && units[i]->name[1] == name[1]) {
                return units[i];
            }

        }

         return nullptr;
    }


bool Base::setNeutralObjects (Field *field){
    
    ConcreteHealthPound hp;
    ConcreteBoxWithArmor ba;
    ConcretePowerChemical pc;
    ConcreteWorkbenchForWeapons ww;
    
    //field->setNeutralObject(hp.CreateNeutralObject(), 0, 0);
    
    if (y > x) {
        
        field->setNeutralObject(hp.CreateNeutralObject(), 0, 1);
        field->setNeutralObject(ba.CreateNeutralObject(), y, y-1);
         
        if ((y+1) % 2 == 0){
            field->setNeutralObject(pc.CreateNeutralObject(), (y+1)/2-1,(y+1)/2);
            field->setNeutralObject(ww.CreateNeutralObject(), (y+1)/2,(y+1)/2);

        } else {
            field->setNeutralObject(pc.CreateNeutralObject(), y/2-1,y/2);
            field->setNeutralObject(ww.CreateNeutralObject(), y/2,y/2+1);

        }
        
        
    } else {
        field->setNeutralObject(hp.CreateNeutralObject(), x-1, x);
        field->setNeutralObject(ba.CreateNeutralObject(), 1, 0);
         
        if ((x+1) % 2 == 0){
            field->setNeutralObject(ww.CreateNeutralObject(), (x+1)/2-1,(x+1)/2-1);
            field->setNeutralObject(pc.CreateNeutralObject(), (x+1)/2,(x+1)/2-1);

        } else {
            field->setNeutralObject(pc.CreateNeutralObject(), x/2+1,x/2);
            field->setNeutralObject(ww.CreateNeutralObject(), x/2,x/2-1);
        }
    }
    
    return true;
}


bool Base::spawn (char typeOfUnit, bool isProtected){
    
    int whatInCell;
    int spawnX, spawnY;
    int numOfUnit = 0;
    
    if (countUnit >= 9){
       // std::cout << "Больше юнитов создать нельзя" << std::endl;
        return false;
    }
    
    switch (typeOfUnit) {
        case '!':
            numOfUnit = 2;
            break;
        case '<':
            numOfUnit = 1;
            break;
        case '>':
            numOfUnit = 1;
            break;
        case '$':
           // std::cout << "Нельзя создать юнита Smoker"<< std::endl;
            return false;
            break;
        default:
           // std::cout << "Не верный тип юнита" << std::endl;
            return false;
            break;
    }
    
    if (x > y){
        spawnX = x-1;
        spawnY = y+1;
    } else {
        spawnX = x+1;
        spawnY = y-1;
    }
    
    whatInCell = field->whatInCell(spawnX, spawnY);
    
    if (whatInCell == 4) {
        
        if (concretCountUnit[numOfUnit] + 2 >= 10) {
           // std::cout << "Больше юнитов этого типа создать нельзя" << std::endl;
            return false;
        }
        
        for (int i = 0; i < 9; i++) {
            
            if (units[i] == nullptr) {
                concretCountUnit[numOfUnit] += 2;
                units[i] = createUnit(numOfUnit, concretCountUnit[numOfUnit]+'0');
                units[i]->Attach(this);
                units[i]->setXY(spawnX, spawnY);
                field->setUnit(units[i], spawnX, spawnY);
                
                log->write(adapter.adaptSpawn(units[i]->getName(),units[i]->getX(), units[i]->getY()));
                units[i]->setLogOut(log);
                countUnit++;
                break;
            }
            
        }
    } else {
        
       // std::cout << "Ошибка создания юнита. База: " << name << std::endl;
        return false;
    }
    
    
    
    return true;
}



BaseSnapshot* Base::saveBase(){
    
    std::vector<std::string> names;
    std::vector<int> h;
    std::vector<int> a;
    std::vector<int> p;
    std::vector<bool> blocAtt;
    std::vector<int> ux;
    std::vector<int> uy;
    for (int i = 0; i < 9; i++){
        
        if (units[i]){
            
            names.push_back(units[i]->getName());
            h.push_back(units[i]->health.getPoint());
            a.push_back(units[i]->armor.getPoint());
            p.push_back(units[i]->attack.getPoint());
            ux.push_back(units[i]->getX());
            uy.push_back(units[i]->getY());
            blocAtt.push_back(units[i]->attackIsBlocked);

        }
    }
    return new BaseSnapshot(names, h, a, p, blocAtt, ux, uy, numberUnit, countUnit, x, y, concretCountUnit, name, isProtect);

}

Base::Base(IObserver *game){ this->game = game;}

void Base::restore (BaseSnapshot* snap, ProxyLog *log, Field *field){
    
    this->log = log;
    this->field = field;
    
    this->x = snap->x;
    this->y = snap->y;
    
    this->name = snap->name;
    this->countUnit = snap->countUnit;
    
    this->isProtect = snap->isProtect;
    
    this->concretCountUnit[0] = snap->concretCountUnit[0];
    this->concretCountUnit[1] = snap->concretCountUnit[1];
    this->concretCountUnit[2] = snap->concretCountUnit[2];
    
    field->setBase(name, x, y);
    setNeutralObjects(field);
    
    int numB = name[1] - '0';
    
    for (int i = 0; i < snap->names.size(); i++){
        
        Unit *u;
        
        if (snap->names[i][(numB+1)%2] == '!'){
            
            u = createUnit(2, snap->names[i][(numB)%2]);
            
        } else if (snap->names[i][(numB+1)%2] == '<' || snap->names[i][(numB+1)%2] == '>'){
            
            u = createUnit(1, snap->names[i][(numB)%2]);
            
        } else if (snap->names[i][(numB+1)%2] == '$'){
            
            u = createUnit(0, snap->names[i][(numB)%2]);
            
        } else { return;}
            
            u->setXY(snap->ux[i], snap->uy[i]);
            u->health.setPoint(snap->h[i]);
            u->armor.setPoint(snap->a[i]);
            u->attack.setPoint(snap->p[i]);
            u->attackIsBlocked = snap->blocAtt[i];
            
            
            u->Attach(this);
            u->setLogOut(log);
            
            field->setUnit(u, u->getX(), u->getY());
            units[i] = u;
 
    }
        
    units[0]->Attach(game);
    
    
}


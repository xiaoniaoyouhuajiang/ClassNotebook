#include <iostream>
#include <cstdlib>
#include <ctime>
#include "NeutralObject.h"
#include "Units.h"


NeutralObject& NeutralObject::operator += (Unit& unit){
    this->action(unit);
    return *this;
}


NeutralObject::NeutralObject(){
    this->hitPoint = 1000;
    this->type = '.';
}

void NeutralObject::getDamage(int damage){
    this->hitPoint -= damage;
    if (hitPoint>1){
        this->~NeutralObject();
        std::cout<<"Object "<<this->type<<" get damage and  destroy"<<std::endl;
    }
    else{
        std::cout<<"Object "<<this->type<<" get damage. HP:"<<this->hitPoint<<std::endl;
    }
}


//-----------------------------------------------------//

Bonfire::Bonfire(){
    this->hitPoint = 50;
    this->healing = 10;
    this->type = '&';
    
}

void Bonfire::action(Unit &unit){
    if(healing){
    unit.hitPoint += healing;
        std::cout<<"Bonfire: Unit "<<unit.type<<"get rest. HP was increased by "<<healing<<"New HP: "<<unit.hitPoint<<std::endl;
        healing = 0;
        type = '-';
    }
    else{
        std::cout<<"Bonfire: the fire has already gone out"<<std::endl;
    }
}


//-----------------------------------------------------//


MrWitcher::MrWitcher(){
    this->nerves = 1;
    this->type = '@';
}

void MrWitcher::action(Unit &unit){
    (this->nerves)--;
    if(nerves == 0){
        std::cout<<"Ведьмак: Хм."<<std::endl;
        //killing this bastard
        unit.getDamage(1000);
        nerves = 10;
    }
    else{
        srand(time(0));
        int i = rand()%5;
        switch (i) {
            case 0:
                std::cout<<"Ведьмак: Хм..."<<std::endl;
                break;
            case 1:
                std::cout<<"Ведьмак: Разойдись свинопасы. Или господин ведьмак вам таких тумаков отвесит, вовек не забудете."<<std::endl;
                break;
            case 2:
                std::cout<<"Ведьмак: Где тут дрын какой-нибудь?! Тебе меня уговаривать не придется!"<<std::endl;
                break;
            case 3:
               std::cout<<"Ведьмак: Поговорим сначала о награде"<<std::endl;
                break;
            case 4:
               std::cout<<"*Господин Ведьмак нервно дышит перегаром, осуждающе смотря на Вас*"<<std::endl;
                break;
                
            default:
                break;
        }
        
    }
}


//-----------------------------------------------------//


Bird::Bird(){
    this->hitPoint = 20;
    this->type = '!';
    this->damage = 5;
}

Bird::Bird(int damage){
    this->damage = damage;
}

void Bird::action(Unit &unit){
    std::cout<<"Bird: tweet!"<<std::endl;
    unit.getDamage(damage);
    
}

//-----------------------------------------------------//

Grave::Grave(){
    this->hitPoint = 100;
    this->type = '+';
}

void Grave::action(Unit &unit){
    std::cout<<"Just a grave"<<std::endl;
}

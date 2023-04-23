#include "landscape.h"


bool Proxy::moving(){
    return true;
}

bool Proxy::notMoving(){
    return false;
}

Forest::Forest(){
    this->sym = '|';
}

bool Forest::interaction(Unit* unit){
    if (unit->sym == 'G'){
        return land.notMoving();
    }
    return 1;
}

Plain::Plain(){
    this->sym = ' ';
}

bool Plain::interaction (Unit* unit){
    if (unit->sym == 'G'){
        unit->force += 25;
        return land.moving();
    }
    return 1;
}

Swamp::Swamp(){
    this->sym = '_';
}

bool Swamp::interaction(Unit* unit){
    if (unit->sym == 'G'){
        unit->force -=25;
        return land.moving();
    }
    if (unit->sym == 'S'){
        return 0;
    }
    return 1;
}

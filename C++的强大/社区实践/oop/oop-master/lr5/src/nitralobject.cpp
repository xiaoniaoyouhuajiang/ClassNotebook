#include "nitralobject.h"


bool NitralObject::Compressor::compress(Unit* unit){
    return inter->compress(unit);
}

Stone::Stone(){
    this->sym = 's';
}

bool Stone::WarriorsInteraction::compress(Unit *unit){
    return 0;
}

bool Stone::MagesInteraction::compress(Unit *unit){
    return 0;
}

bool Stone::SaboteursInteraction::compress(Unit *unit){
    return 0;
}

bool Stone::strategy(Unit* unit){
    if (unit->sym == 'G' || unit->sym == 'S'){
        comp = new Compressor(new WarriorsInteraction);
        return comp->compress(unit);
    }
    if (unit->sym == 'W' || unit->sym == 'H'){
        comp = new Compressor(new MagesInteraction);
        return comp->compress(unit);
    }
    if (unit->sym == 'J' || unit->sym == 'K'){
        comp = new Compressor(new SaboteursInteraction);
        return comp->compress(unit);
    }
}

Gold::Gold(){
    this->sym = 'g';
}

bool Gold::WarriorsInteraction::compress(Unit *unit){
    return 1;
}

bool Gold::MagesInteraction::compress(Unit *unit){
    return 1;
}

bool Gold::SaboteursInteraction::compress(Unit *unit){
    return 1;
}

bool Gold::strategy(Unit* unit){
    if (unit->sym == 'G' || unit->sym == 'S'){
        comp = new Compressor(new WarriorsInteraction);
        return comp->compress(unit);
    }
    if (unit->sym == 'W' || unit->sym == 'H'){
        comp = new Compressor(new MagesInteraction);
        return comp->compress(unit);
    }
    if (unit->sym == 'J' || unit->sym == 'K'){
        comp = new Compressor(new SaboteursInteraction);
        return comp->compress(unit);
    }
}

ForceWell::ForceWell(){
    this->sym = 'f';
}

bool ForceWell::WarriorsInteraction::compress(Unit *unit){
    unit->force += 50;
    unit->compFlag = 0;
    return 0;
}

bool ForceWell::MagesInteraction::compress(Unit *unit){
    unit->force += 100;
    unit->compFlag = 0;
    return 0;
}

bool ForceWell::SaboteursInteraction::compress(Unit *unit){
    unit->force += 1;
    unit->compFlag = 0;
    return 0;
}

bool ForceWell::strategy(Unit* unit){
    if (unit->compFlag){
        if (unit->sym == 'G' || unit->sym == 'S'){
            comp = new Compressor(new WarriorsInteraction);
            return comp->compress(unit);
        }
        if (unit->sym == 'W' || unit->sym == 'H'){
            comp = new Compressor(new MagesInteraction);
            return comp->compress(unit);
        }
        if (unit->sym == 'J' || unit->sym == 'K'){
            comp = new Compressor(new SaboteursInteraction);
            return comp->compress(unit);
        }
    }
    return 0;
}

LifeWell::LifeWell(){
    this->sym = 'l';
}

bool LifeWell::WarriorsInteraction::compress(Unit *unit){
    unit->hp += 100;
    unit->compFlag = 0;
    return 0;
}

bool LifeWell::MagesInteraction::compress(Unit *unit){
    unit->hp += 50;
    unit->compFlag = 0;
    return 0;
}

bool LifeWell::SaboteursInteraction::compress(Unit *unit){
    unit->hp += 1;
    unit->compFlag = 0;
    return 0;
}

bool LifeWell::strategy(Unit* unit){
    if (unit->compFlag){
        if (unit->sym == 'G' || unit->sym == 'S'){
            comp = new Compressor(new WarriorsInteraction);
            return comp->compress(unit);
        }
        if (unit->sym == 'W' || unit->sym == 'H'){
            comp = new Compressor(new MagesInteraction);
            return comp->compress(unit);
        }
        if (unit->sym == 'J' || unit->sym == 'K'){
            comp = new Compressor(new SaboteursInteraction);
            return comp->compress(unit);
        }
    }
    return 0;
}

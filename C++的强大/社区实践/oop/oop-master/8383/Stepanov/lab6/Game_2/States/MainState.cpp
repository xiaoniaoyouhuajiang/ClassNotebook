//
//  MainState.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 09.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "MainState.hpp"

MainState::MainState(){
    
    current = new firstState();
    next = new secondState();
    
    state = 0;
}

MainState::~MainState(){
    
    delete current;
    delete next;
}

bool MainState::checkState (std::string s){
    
    
    return current->checkState(s);
}

bool MainState::checkState (char s){
    
    
    return current->checkState(s);
}


void MainState::nextState(){
    State *a;
    
    a = current;
    current = next;
    next = a;
    
    state ++;
    state %= 2;
    
}

int MainState::getState() {return state;}

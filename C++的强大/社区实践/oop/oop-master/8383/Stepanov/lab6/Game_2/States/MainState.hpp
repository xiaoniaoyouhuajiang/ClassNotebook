//
//  MainState.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 09.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef MainState_hpp
#define MainState_hpp

//#include "State.hpp"
#include "firstState.hpp"
#include "secondState.hpp"


class MainState {
    
    State *current;
    State *next;
    
    int state;
    
public:
    
    MainState();
    ~MainState();
    
    bool checkState (std::string s);
    bool checkState (char s);
    
    void nextState();
    int getState();

    
    
};

#endif /* MainState_hpp */

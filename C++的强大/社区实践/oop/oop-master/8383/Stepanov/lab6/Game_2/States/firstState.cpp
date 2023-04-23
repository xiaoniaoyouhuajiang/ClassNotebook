//
//  firstState.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 09.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "firstState.hpp"

bool  firstState::checkState (std::string s){
    
        
    if (s[1] <= '9' && s[1] >= '1') return true;
 
    return false;
    
}

bool  firstState::checkState (char s){
    
    
    if (s == '1') return true;
 
    return false;
    
}

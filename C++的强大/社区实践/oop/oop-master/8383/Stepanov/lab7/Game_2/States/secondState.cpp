//
//  secondState.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 09.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "secondState.hpp"

bool  secondState::checkState (std::string s){
    
        
    if (s[0] <= '9' && s[0] >= '1') return true;
 
    return false;
    
}

bool  secondState::checkState (char s){
    
    
    if (s == '2') return true;
 
    return false;
    
}

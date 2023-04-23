//
//  ProxyLandscape.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ProxyLandscape.hpp"

Proxy::Proxy (Landscape * l){
    landscape = l;
    name = l->getName();
}

bool Proxy::doSomething (Unit* u){
    
    char *uname = u->getName();
    
    if (name == '#'){                                           // brush
            
        if (uname[0] == '<' || uname[1] == '>'){            // shooter
            u->attackIsBlocked = true;
        } else if (uname[0] == '!' || uname[1] == '!') {    // runner
            u->incHealth(-1);
        } else {                                            // smoker
            u->incArmor(-1);
        }
        
    } else if (name == '(') {                                   // deepPuddel
       
        if (uname[0] == '<' || uname[1] == '>'){             //shooter
           u->incAttack(-1);
        } else if (uname[0] == '!' || uname[1] == '!') {    // runner
            u->attackIsBlocked = true;
        } else {                                            // smoker
            return false;
        }
    } else {                                                    // ground
        u->attackIsBlocked = false;                         // for all units
    }
    return true;
}

char Proxy::getName (){
    return landscape->getName();
}


//
//  ErrorSpawn.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 18.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ErrorSpawn_hpp
#define ErrorSpawn_hpp

#include <iostream>


class ErrorSpawn {
    
private:
    char base;
    char unit;
    
public:
    
    ErrorSpawn(char base, char unit);
    
    char getBase ();
    char getUnit ();
    
    void writeErr ();
    
    
};


#endif /* ErrorSpawn_hpp */

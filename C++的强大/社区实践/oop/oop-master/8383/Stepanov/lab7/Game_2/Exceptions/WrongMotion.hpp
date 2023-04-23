//
//  WrongMotion.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 18.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef WrongMotion_hpp
#define WrongMotion_hpp

#include <iostream>
#include <string>

class WrongMotion {
    
private:
    std::string name;
    
public:
    
    WrongMotion (std::string name);
    std::string getMotion ();
    void writeErr ();
};

#endif /* WrongMotion_hpp */

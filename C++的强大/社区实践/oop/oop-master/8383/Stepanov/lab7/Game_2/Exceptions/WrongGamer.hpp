//
//  WrongGamer.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 18.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef WrongGamer_hpp
#define WrongGamer_hpp

#include <iostream>
#include <string>


class WrongGamer {
    
private:
    
    int type;
    
    std::string name;

    
public:
    
    WrongGamer (std::string name);
    WrongGamer (char name);

    std::string getName();
    
    void writeErr();
    
    
};

#endif /* WrongGamer_hpp */

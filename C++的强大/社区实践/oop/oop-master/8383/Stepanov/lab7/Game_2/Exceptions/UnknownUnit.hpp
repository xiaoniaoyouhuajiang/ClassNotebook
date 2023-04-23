//
//  UnknownUnit.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 18.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef UnknownUnit_hpp
#define UnknownUnit_hpp

#include <iostream>
#include <string>

class UnknownUnit {

private:
    std::string name;

public:
    
    UnknownUnit(std::string name);
    std::string getName();
    void writeErr();
    
};

#endif /* UnknownUnit_hpp */

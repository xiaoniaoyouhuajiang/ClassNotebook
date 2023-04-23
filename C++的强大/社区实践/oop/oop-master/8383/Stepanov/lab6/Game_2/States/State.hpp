//
//  State.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 09.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include <string>

class State {

public:

    virtual bool checkState (std::string s) = 0;
    virtual bool checkState (char s) = 0;

};

#endif /* State_hpp */

//
//  firstState.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 09.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef firstState_hpp
#define firstState_hpp

#include "State.hpp"

class firstState: public State {

public:

    bool checkState (std::string s) override;

    bool checkState (char s) override;
};

#endif /* firstState_hpp */

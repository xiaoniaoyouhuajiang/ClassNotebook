//
//  secondState.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 09.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef secondState_hpp
#define secondState_hpp

#include "State.hpp"

class secondState: public State {

public:

    bool checkState (std::string s) override;

    bool checkState (char s) override;
};

#endif /* secondState_hpp */

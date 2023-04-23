//
//  Game.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 25.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <string>

#include "Base.hpp"
#include "Field.hpp"
#include "Landscape.hpp"
#include "ProxyLandscape.hpp"

#include "Facade.hpp"
#include "CommandHandler.hpp"
#include "SpawnHandler.hpp"
#include "ExitHandler.hpp"
#include "MotionHandler.hpp"
#include "SpecHandler.hpp"
#include "Mediator.hpp"


#define SIZE 7

class Game {
    
    Field *field;
    Base *first;
    Base *second;
    int height, width;
    
    CommandHandler actionHandler;
    Mediator mediator;
    int specialFirst = 0;
    int specialSecond = 0;
    
public:
    void startGame();
    void printField();
    void printPoints ();
    
    
    bool action (bool &endGame);
    
};

#endif /* Game_hpp */


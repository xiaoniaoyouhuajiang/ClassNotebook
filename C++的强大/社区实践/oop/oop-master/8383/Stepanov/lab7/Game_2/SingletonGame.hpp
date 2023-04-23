//
//  SingletonGame.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 09.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef SingletonGame_hpp
#define SingletonGame_hpp

#include "Game.hpp"
#include <string>

class SingletonGame {
    
    Game *g = nullptr;
    
public:
   void startGame();
    
};

#endif /* SingletonGame_hpp */

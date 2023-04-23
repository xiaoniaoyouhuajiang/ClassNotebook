//
//  SingletonGame.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 09.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "SingletonGame.hpp"

void SingletonGame::startGame(){
    
    
    std::string s;
    bool newGame = false;
    
    int size = 0;
    bool fastGame = true;

    
    do{
        
        std::cout << "Быстрая игра  y/n" << std::endl;
        
        std::cin >> s;
        
        if (s == "y" ) fastGame = false;
        else if (s != "n"){
            newGame = true;
            continue;
        }
        
        std::cout << "Размер поля (6 < x < 21)" << std::endl;
        
        std::cin >> size;
        
        if (std::cin.fail()){
            newGame = true;
            std::cin.clear();
            std::cin.ignore(32767,'\n');
            continue;
        } else if (size <= 6 || size >= 21) {
            newGame = true;
            continue;
        }
        
        
        newGame = false;
    
        if (g == nullptr) g = new Game(fastGame, size);
    
        g->startGame();
    
        delete g;
        g = nullptr;
    
        std::cout << "Начать новую игру y/n" << std::endl;
    
        std::cin >> s;
        
        if (s.length() == 1 && s == "y"){
            newGame = true;
        }
        
    } while (newGame);
    
    
}

#ifndef PplayGameTem_hpp
#define PplayGameTem_hpp

#include <stdio.h>
#include "playgame.hpp"


template <typename T, int n>
class PlayGameTemplate;


template <typename T>
class PlayGameTemplate<T, 1>
{
public:
    PlayGameTemplate(T gameRules){
        numOfPlayers = 1;
        this->gameRules = gameRules;
    }
    void startGame(){
        PlayGame* game = PlayGame::GetInstance(gameRules, numOfPlayers);
        game->startGame();
    }
private:
    T gameRules;
    int numOfPlayers;
};


template <typename T>
class PlayGameTemplate<T, 2>
{
public:
    PlayGameTemplate(T gameRules){
        numOfPlayers = 2;
        this->gameRules = gameRules;
    }
    void startGame(){
       PlayGame* game = PlayGame::GetInstance(gameRules, numOfPlayers);
        game->startGame();
    }
private:
    T gameRules;
    int numOfPlayers;
};


#endif /* PplayGameTem_hpp */

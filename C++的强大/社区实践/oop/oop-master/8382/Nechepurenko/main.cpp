#include <iostream>
#include <utility>
#include <string>
#include "headers/game.hpp"
#include "headers/neutral.hpp"
#include "headers/facade.hpp"
#include "headers/parser.hpp"
#include "headers/serializer.hpp"

int main(){
    auto facade = new Facade(5,5);
    auto res = facade->mainLoop();
    delete facade;
    return 0;
}


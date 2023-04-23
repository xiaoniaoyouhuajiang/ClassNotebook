#ifndef player1_hpp
#define player1_hpp

#include <stdio.h>
#include "StateAbstract.hpp"


class Player1 : public State {
 public:
    ACTION getInputAction() override{
        std::cout << "Player1 turn!\n";
        return input();
    };
};

#endif /* player1_hpp */
